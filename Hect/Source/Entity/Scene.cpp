#include "Hect.h"

using namespace hect;

Scene::Scene() :
    _activatedEntityCount(0),
    _nextEntityId(0),
    _entityData(InitialPoolSize),
    _entityComponents(InitialPoolSize)
{
}

Scene::~Scene()
{
    for (System* system : _systems)
    {
        system->removeAllEntities();
    }
}

void Scene::refresh()
{
    for (Entity::Id id : _activatedEntityIds)
    {
        Entity& entity = _entityWithId(id);
        for (System* system : _systems)
        {
            if (system->includesEntity(entity))
            {
                system->addEntity(entity);
            }
        }

        ++_activatedEntityCount;
    }
    _activatedEntityIds.clear();

    for (Entity::Id id : _destroyedEntityIds)
    {
        Entity& entity = _entityWithId(id);
        for (System* system : _systems)
        {
            if (system->includesEntity(entity))
            {
                system->removeEntity(entity);
            }
        }

        EntityData& data = _entityData[id];
        if (data.isActivated())
        {
            --_activatedEntityCount;
        }

        // Clear entity data
        _entityComponents[id].clear();
        _entityData[id] = EntityData();

        // Re-use this id
        _nextEntityIds.push(id);
    }
    _destroyedEntityIds.clear();
}

void Scene::addSystem(System& system)
{
    _systems.push_back(&system);

    // Add any entities the systems is filtered for
    size_t addedEntities = 0;
    Entity::Id id = 0;
    while (addedEntities < _activatedEntityCount)
    {
        Entity entity = _entityWithId(id);
        if (entity)
        {
            if (entity.isActivated() && system.includesEntity(entity))
            {
                ++addedEntities;
                system.addEntity(Entity(*this, id));
            }
        }

        ++id;
    }
}

void Scene::removeSystem(System& system)
{
    system.removeAllEntities();
    _systems.erase(std::remove(_systems.begin(), _systems.end(), &system), _systems.end());
}

Entity Scene::createEntity()
{
    Entity::Id id;

    // Re-use IDs as often as possible to avoid resizing the pool
    if (!_nextEntityIds.empty())
    {
        id = _nextEntityIds.back();
        _nextEntityIds.pop();
    }
    else
    {
        id = _nextEntityId++;

        // Resize the pool if needed
        if (id >= _entityComponents.size())
        {
            size_t size = _entityComponents.size() * 2;
            _entityData.resize(size);
            _entityComponents.resize(size);
        }
    }

    _entityData[id].setNull(false);
    return Entity(*this, id);
}

void Scene::save(DataValue& dataValue) const
{
    DataValue::Array elements;
    for (Entity::Id id = 0; id < _entityData.size(); ++id)
    {
        Entity entity = _entityWithId(id);
        if (entity && entity.isActivated())
        {
            DataValue entityDataValue;
            entity.save(entityDataValue);
            elements.push_back(entityDataValue);
        }
    }

    DataValue::Object members;
    members["entities"] = DataValue(elements);
    dataValue = DataValue(members);
}

void Scene::save(WriteStream& stream) const
{
    for (Entity::Id id = 0; id < _entityData.size(); ++id)
    {
        Entity entity = _entityWithId(id);
        if (entity && entity.isActivated())
        {
            entity.save(stream);
        }
    }
}

void Scene::load(const DataValue& dataValue, AssetCache& assetCache)
{
    for (const DataValue& entityValue : dataValue["entities"])
    {
        Entity entity = createEntity();
        entity.load(entityValue, assetCache);
        entity.activate();
    }
}

void Scene::load(ReadStream& stream, AssetCache& assetCache)
{
    while (!stream.endOfStream())
    {
        Entity entity = createEntity();
        entity.load(stream, assetCache);
        entity.activate();
    }
}

Entity Scene::_entityWithId(Entity::Id id) const
{
    if (id < _entityData.size())
    {
        return Entity(*const_cast<Scene*>(this), id);
    }

    return Entity(); // Outside of range
}

Entity Scene::_cloneEntity(const Entity& entity)
{
    Entity clone = createEntity();

    auto& components = _entityComponents[entity._id];
    for (auto& pair : components)
    {
        BaseComponent* component = pair.second.get();

        // Clone the component
        BaseComponent::Ref clonedComponent(component->clone());

        // Add the clone component to the cloned entity
        _addComponentWithoutReturn(clone, clonedComponent);
    }

    return clone;
}

void Scene::_destroyEntity(Entity& entity)
{
    Entity::Id id = entity._id;
    EntityData& data = _entityData[id];

#ifdef HECT_DEBUG
    if (entity.isNull())
    {
        throw Error("Entity is null");
    }
    else if (data.isDestroyed())
    {
        throw Error("Entity is already destroyed");
    }
#endif

    data.setDestroyed(true);
    _destroyedEntityIds.push_back(id);
}

void Scene::_activateEntity(Entity& entity)
{
    Entity::Id id = entity._id;
    EntityData& data = _entityData[id];

#ifdef HECT_DEBUG
    if (entity.isNull())
    {
        throw Error("Entity is null");
    }
    else if (data.isActivated())
    {
        throw Error("Entity is already activated");
    }
#endif

    data.setActivated(true);
    _activatedEntityIds.push_back(id);
}

bool Scene::_isActivated(const Entity& entity) const
{
    return _entityData[entity._id].isActivated();
}

bool Scene::_isNull(const Entity& entity) const
{
    return _entityData[entity._id].isNull();
}

void Scene::_addComponentWithoutReturn(Entity& entity, const BaseComponent::Ref& component)
{
    Entity::Id id = entity._id;
    EntityData& data = _entityData[id];

    ComponentTypeId typeId = component->componentTypeId();

#ifdef HECT_DEBUG
    if (entity.isNull())
    {
        throw Error("Entity is null");
    }
    else if (entity.isActivated())
    {
        throw Error("Entity is activated");
    }
    else if (data.hasComponent(typeId))
    {
        throw Error(format("Entity already has a component with type id '%d'", typeId));
    }
#endif

    data.setHasComponent(typeId, true);
    _entityComponents[id][typeId] = component;
}