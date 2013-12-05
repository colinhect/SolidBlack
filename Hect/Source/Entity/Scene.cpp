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
    // All entities in the scene will be invalidated when the scene is
    // destroyed, so we remove the entities from all of the scenes first
    for (System* system : _systems)
    {
        system->removeAllEntities();
    }
}

void Scene::refresh()
{
    // Add all activated entities to systems that include them
    for (Entity::Id id : _activatedEntityIds)
    {
        Entity entity = _entityWithId(id);
        for (System* system : _systems)
        {
            if (system->includesEntity(entity))
            {
                system->addEntity(entity);
            }
        }

        // Maintain the activated entity count
        ++_activatedEntityCount;
    }
    _activatedEntityIds.clear();

    // Remove all destroyed entities from systems that include them
    for (Entity::Id id : _destroyedEntityIds)
    {
        Entity entity = _entityWithId(id);
        for (System* system : _systems)
        {
            if (system->includesEntity(entity))
            {
                system->removeEntity(entity);
            }
        }

        // Maintain the activated entity count
        if (entity.isActivated())
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
    // Add the system to the scene
    _systems.push_back(&system);

    // Add any entities the systems is filtered for
    for (Entity::Id id = 0; id < _entityData.size(); ++id)
    {
        Entity entity = _entityWithId(id);
        if (entity && entity.isActivated() && system.includesEntity(entity))
        {
            system.addEntity(entity);
        }
    }
}

void Scene::removeSystem(System& system)
{
    // Remove all entities from the system
    system.removeAllEntities();

    // Remove the system from the scene
    _systems.erase(std::remove(_systems.begin(), _systems.end(), &system), _systems.end());
}

Entity Scene::createEntity()
{
    Entity::Id id;

    // Re-use ids as often as possible to avoid resizing the pool
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

    // Set the entity as no longer being null; the rest of the data is
    // properly initialized
    _entityData[id].setNull(false);
    return Entity(*this, id);
}

void Scene::save(DataValue& dataValue) const
{
    // Save each activated entity to a separate data value
    DataValue::Array elements;
    for (Entity::Id id = 0; id < _entityData.size(); ++id)
    {
        Entity entity = _entityWithId(id);
        if (entity && entity.isActivated())
        {
            // Save the entity to a data value
            DataValue entityDataValue;
            entity.save(entityDataValue);

            // Add the data value to the elements
            elements.push_back(entityDataValue);
        }
    }

    // Save the entire scene as a data value object with the entities as a
    // member
    DataValue::Object members;
    members["entities"] = DataValue(elements);
    dataValue = DataValue(members);
}

void Scene::save(WriteStream& stream) const
{
    // Serialize each activated entity to the stream
    for (Entity::Id id = 0; id < _entityData.size(); ++id)
    {
        Entity entity = _entityWithId(id);
        if (entity && entity.isActivated())
        {
            // Serialize the entity
            entity.save(stream);
        }
    }
}

void Scene::load(const DataValue& dataValue, AssetCache& assetCache)
{
    // For each entity data value
    for (const DataValue& entityValue : dataValue["entities"])
    {
        // Create an entity and load the components
        Entity entity = createEntity();
        entity.load(entityValue, assetCache);
        entity.activate();
    }
}

void Scene::load(ReadStream& stream, AssetCache& assetCache)
{
    // While there is still data in the stream
    while (!stream.endOfStream())
    {
        // Create an entity and load the components
        Entity entity = createEntity();
        entity.load(stream, assetCache);
        entity.activate();
    }
}

Entity Scene::_entityWithId(Entity::Id id) const
{
    return Entity(*const_cast<Scene*>(this), id);
}

Entity Scene::_cloneEntity(const Entity& entity)
{
    // Create the cloned entity
    Entity clone = createEntity();

    // For each component in the source entity
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

    if (data.isNull())
    {
        throw Error("Entity is null");
    }
    else if (data.isDestroyed())
    {
        throw Error("Entity is already destroyed");
    }

    // Set the entity as destroyed and enqueue it to be removed from the
    // systems
    data.setDestroyed(true);
    _destroyedEntityIds.push_back(id);
}

void Scene::_activateEntity(Entity& entity)
{
    Entity::Id id = entity._id;
    EntityData& data = _entityData[id];

    if (data.isNull())
    {
        throw Error("Entity is null");
    }
    else if (data.isActivated())
    {
        throw Error("Entity is already activated");
    }

    // Set the entity as activated and enqueue it to be removed from the
    // systems
    data.setActivated(true);
    _activatedEntityIds.push_back(id);
}

bool Scene::_isActivated(const Entity& entity) const
{
    // Check the entity data to see if the entity is activated
    Entity::Id id = entity._id;
    const EntityData& data = _entityData[id];
    return data.isActivated();
}

bool Scene::_isNull(const Entity& entity) const
{
    // Check the entity data to see if the entity is null
    Entity::Id id = entity._id;
    const EntityData& data = _entityData[id];
    return data.isNull();
}

void Scene::_addComponentWithoutReturn(Entity& entity, const BaseComponent::Ref& component)
{
    Entity::Id id = entity._id;
    EntityData& data = _entityData[id];

    ComponentTypeId typeId = component->componentTypeId();

    if (data.isNull())
    {
        throw Error("Entity is null");
    }
    else if (data.isActivated())
    {
        throw Error("Entity is activated");
    }
    else if (data.hasComponent(typeId))
    {
        throw Error(format("Entity already has a component with type id '%d'", typeId));
    }

    // Set the flag in the entity data to include the component type
    data.setHasComponent(typeId, true);
    _entityComponents[id][typeId] = component;
}