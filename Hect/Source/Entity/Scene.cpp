#include "Hect.h"

using namespace hect;

Scene::Scene() :
    _entityCount(0),
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

        // Clear entity data
        _entityComponents[id].clear();
        _entityData[id] = EntityData();

        // Re-use this id
        _nextEntityIds.push(id);

        --_entityCount;
    }
    _destroyedEntityIds.clear();
}

void Scene::addSystem(System& system)
{
    _systems.push_back(&system);

    // Add any entities the systems is filtered for
    size_t addedEntities = 0;
    Entity::Id id = 0;
    while (addedEntities < _entityCount)
    {
        Entity entity = _entityWithId(id);
        if (entity)
        {
            ++addedEntities;
            if (entity.isActivated() && system.includesEntity(entity))
            {
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
    ++_entityCount;
    return Entity(*this, id);
}

Entity Scene::_entityWithId(Entity::Id id)
{
    if (id < _entityData.size())
    {
        return Entity(*this, id); // Inside of range, still might be null
    }

    return Entity(); // Outside of range
}

Entity Scene::_cloneEntity(Entity entity)
{
    Entity clone = createEntity();

    auto& components = _entityComponents[entity._id];
    for (auto& pair : components)
    {
        _addComponentWithoutReturn(clone, pair.second->_clone());
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

    auto& components = _entityComponents[id];
    for (auto& pair : components)
    {
        // Give the component the entity id and scene to be sused in
        // BaseComponent::entity()
        const BaseComponent::Ref& component = pair.second;
        component->_scene = this;
        component->_entityId = id;
    }

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

    ComponentTypeId typeId = component->_componentTypeId();

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