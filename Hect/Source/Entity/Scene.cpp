#include "Hect.h"

using namespace hect;

Scene::Scene() :
    _entityCount(0),
    _nextId(0),
    _deactivatedAttributes(InitialPoolSize),
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
    for (Entity& entity : _deactivatedEntities)
    {
        EntityAttributes& deactivatedAttributes = _deactivatedAttributes[entity._id];
        EntityAttributes& attributes = _attributes[entity._id];
        bool wasReactivated = attributes.hasAttribute(EntityAttributeBit::Activated);

        // The entity was deactivated and reactivated since last refresh
        if (wasReactivated)
        {
            EntityAttributes difference = deactivatedAttributes.difference(attributes);

            // Remove the entity from all systems where it was effectively removed from
            for (System* system : _systems)
            {
                if (system->requiredAttributes().contains(difference))
                {
                    system->removeEntity(entity);
                }
            }
        }

        // The entity was deactivated but not reactivated since last refresh
        else
        {
            // Remove the entity from all systems it was in on deactivation
            for (System* system : _systems)
            {
                if (deactivatedAttributes.contains(system->requiredAttributes()))
                {
                    system->removeEntity(entity);
                }
            }
        }

        attributes.setAttribute(EntityAttributeBit::MarkedForDeactivation, false);
        attributes.setAttribute(EntityAttributeBit::Activated, false);
    }
    _deactivatedEntities.clear();

    // Add all recently activated entities to the systems they belong to
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

        attributes.setAttribute(EntityAttributeBit::MarkedForActivation, false);
        attributes.setAttribute(EntityAttributeBit::Activated, true);
    }
    _activatedEntities.clear();

    for (Entity& entity : _destroyedEntities)
    {
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
        EntityAttributes& attributes = _attributes[id];
        if (attributes.hasAttribute(EntityAttributeBit::Exists))
        {
            ++addedEntities;
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
            _deactivatedAttributes.resize(size);
            _attributes.resize(size);
            _components.resize(size);
        }
    }

    _attributes[id].setAttribute(EntityAttributeBit::Exists, true);
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
    else if (attributes.hasAttribute(EntityAttributeBit::MarkedForDestruction))
    {
        throw Error("Entity is already marked for destruction");
    }
#endif

    attributes.setAttribute(EntityAttributeBit::MarkedForDestruction, true);

    if (_isActivated(entity) && !attributes.hasAttribute(EntityAttributeBit::MarkedForDeactivation))
    {
        _deactivateEntity(entity);
    }

    _destroyedEntities.push_back(entity);
}

void Scene::_activateEntity(Entity& entity)
{
    EntityAttributes& attributes = _attributes[entity._id];

#ifdef HECT_DEBUG
    if (_isActivated(entity) && !attributes.hasAttribute(EntityAttributeBit::MarkedForDeactivation))
    {
        throw Error("Entity is already activated");
    }
    else if (attributes.hasAttribute(EntityAttributeBit::MarkedForActivation))
    {
        throw Error("Entity is already marked for activation");
    }
#endif

    attributes.setAttribute(EntityAttributeBit::MarkedForActivation, true);

    auto& components = _components[entity._id];
    for (auto& pair : components)
    {
        const BaseComponent::Ref& component = pair.second;
        component->_scene = this;
        component->_entityId = entity._id;
    }

    _activatedEntities.push_back(entity);
}

void Scene::_deactivateEntity(Entity& entity)
{
    EntityAttributes& attributes = _attributes[entity._id];

#ifdef HECT_DEBUG
    if (!_isActivated(entity))
    {
        throw Error("Entity is already deactivated");
    }
    else if (attributes.hasAttribute(EntityAttributeBit::MarkedForDeactivation))
    {
        throw Error("Entity is already marked for deactivation");
    }
#endif

    attributes.setAttribute(EntityAttributeBit::MarkedForDeactivation, true);

    auto& components = _components[entity._id];
    for (auto& pair : components)
    {
        const BaseComponent::Ref& component = pair.second;
        component->_scene = nullptr;
        component->_entityId = 0;
    }

    // Keep the attributes the entity had on deactivation
    _deactivatedAttributes[entity._id] = _attributes[entity._id];
    _deactivatedEntities.push_back(entity);
}

bool Scene::_isActivated(const Entity& entity) const
{
    return _attributes[entity._id].hasAttribute(EntityAttributeBit::Activated);
}

bool Scene::_isNull(const Entity& entity) const
{
    return !_attributes[entity._id].hasAttribute(EntityAttributeBit::Exists);
}

void Scene::_addComponentWithoutReturn(Entity& entity, const BaseComponent::Ref& component)
{
    ComponentTypeId type = component->_componentTypeId();

#ifdef HECT_DEBUG
    assert(!entity.isNull());
    if(_attributes[entity._id].hasComponent(type))
    {
        throw Error("Attempt to add a component an entity already has");
    }

    if (_isActivated(entity))
    {
        throw Error("Attempt to add a component to an activated entity");
    }
#endif

    // Add the existence of a component of this type to the entity's attributes
    _attributes[entity._id].setHasComponent(type, true);

    // Add the component to the entity's components
    _components[entity._id][type] = component;
}