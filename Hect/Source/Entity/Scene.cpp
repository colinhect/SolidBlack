#include "Hect.h"

using namespace hect;

Scene::Scene() :
    _entityCount(0),
    _nextId(0),
    _attributes(InitialPoolSize),
    _components(InitialPoolSize)
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
    for (Entity& entity : _activatedEntities)
    {
        EntityAttributes& attributes = _attributes[entity._id];

        for (System* system : _systems)
        {
            if (attributes.contains(system->requiredAttributes()))
            {
                system->addEntity(entity);
            }
        }
    }
    _activatedEntities.clear();

    for (Entity& entity : _destroyedEntities)
    {
        EntityAttributes& attributes = _attributes[entity._id];

        for (System* system : _systems)
        {
            if (attributes.contains(system->requiredAttributes()))
            {
                system->removeEntity(entity);
            }
        }

        // Clear entity component/attribute data
        Entity::Id id = entity._id;
        _components[id].clear();
        _attributes[id] = EntityAttributes();

        // Re-use this ID
        _nextIds.push(id);

        --_entityCount;
    }
    _destroyedEntities.clear();
}

void Scene::addSystem(System& system)
{
    _systems.push_back(&system);

    // Add any entities the systems is filtered for
    size_t addedEntities = 0;
    Entity::Id id = 0;
    while (addedEntities < _entityCount)
    {
        Entity entity = entityWithId(id);
        if (entity)
        {
            ++addedEntities;
            EntityAttributes& attributes = _attributes[id];
            if (attributes.contains(system.requiredAttributes()))
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
    if (!_nextIds.empty())
    {
        id = _nextIds.back();
        _nextIds.pop();
    }
    else
    {
        id = _nextId++;

        // Resize the pool if needed
        if (id >= _components.size())
        {
            size_t size = _components.size() * 2;
            _attributes.resize(size);
            _components.resize(size);
        }
    }

    _attributes[id].setNull(false);
    ++_entityCount;
    return Entity(*this, id);
}

Entity Scene::copyEntity(Entity entity)
{
    throw Error("Not implemented");
}

Entity Scene::entityWithId(Entity::Id id)
{
    if (id < _attributes.size())
    {
        return Entity(*this, id); // Inside of range, still might be null
    }

    return Entity(); // Outside of range
}

void Scene::_destroyEntity(Entity& entity)
{
    EntityAttributes& attributes = _attributes[entity._id];

#ifdef HECT_DEBUG
    if (_isNull(entity))
    {
        throw Error("Attempt to destroy a null entity");
    }
    else if (attributes.isDestroyed())
    {
        throw Error("Entity is already destroyed");
    }
#endif

    attributes.setDestroyed(true);
    _destroyedEntities.push_back(entity);
}

void Scene::_activateEntity(Entity& entity)
{
    EntityAttributes& attributes = _attributes[entity._id];

#ifdef HECT_DEBUG
    if (_isNull(entity))
    {
        throw Error("Attempt to activate a null entity");
    }
    else if (attributes.isActivated())
    {
        throw Error("Entity is already activated");
    }
#endif

    attributes.setActivated(true);

    auto& components = _components[entity._id];
    for (auto& pair : components)
    {
        const BaseComponent::Ref& component = pair.second;
        component->_scene = this;
        component->_entityId = entity._id;
    }

    _activatedEntities.push_back(entity);
}

bool Scene::_isActivated(const Entity& entity) const
{
    return _attributes[entity._id].isActivated();
}

bool Scene::_isNull(const Entity& entity) const
{
    return _attributes[entity._id].isNull();
}

void Scene::_addComponentWithoutReturn(Entity& entity, const BaseComponent::Ref& component)
{
    ComponentTypeId type = component->_componentTypeId();

#ifdef HECT_DEBUG
    if (_isNull(entity))
    {
        throw Error("Attempt to add a component to a null entity");
    }
    else if(_attributes[entity._id].hasComponent(type))
    {
        throw Error("Attempt to add a component an entity already has");
    }
    else if (_isActivated(entity))
    {
        throw Error("Attempt to add a component to an activated entity");
    }
#endif

    // Add the existence of a component of this type to the entity's attributes
    _attributes[entity._id].setHasComponent(type, true);

    // Add the component to the entity's components
    _components[entity._id][type] = component;
}