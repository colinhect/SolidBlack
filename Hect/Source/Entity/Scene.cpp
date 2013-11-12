#include "Hect.h"

using namespace hect;

Scene::Scene(size_t entityPoolSize) :
    _nextId(1), // Entity ID 0 is considered null, so start at 1
    _attributes(std::max<size_t>(2, entityPoolSize)),
    _components(std::max<size_t>(2, entityPoolSize))
{
}

void Scene::refresh()
{
    // Add all recently activated entities to the systems they belong to
    for (Entity& entity : _activatedEntities)
    {
        EntityAttributes& attributes = _attributes[entity._id];
        attributes.setActivated(true);

        for (EntitySystem* system : _systems)
        {
            if (attributes.contains(system->requiredAttributes()))
            {
                system->addEntity(entity);
            }
        }
    }
    _activatedEntities.clear();

    // Remove all recently destroyed entities from the systems they belong to
    for (Entity& entity : _destroyedEntities)
    {
        EntityAttributes& attributes = _attributes[entity._id];
        for (EntitySystem* system : _systems)
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
    }
    _destroyedEntities.clear();
}

void Scene::addSystem(EntitySystem& system)
{
    _systems.push_back(&system);
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

    Entity entity(*this, id);
    _attributes[id].setNull(false);
    return entity;
}

void Scene::_activateEntity(const Entity& entity)
{
#ifdef HECT_DEBUG
    if (_isNull(entity))
    {
        throw Error("Attempt to activate a null entity");
    }

    if (_isActivated(entity))
    {
        throw Error("Attempt to activate an activated entity");
    }
#endif

    _activatedEntities.push_back(entity);
}

void Scene::_destroyEntity(const Entity& entity)
{
#ifdef HECT_DEBUG
    if (_isNull(entity))
    {
        throw Error("Attempt to destroy a null entity");
    }
#endif

    _destroyedEntities.push_back(entity);
}

bool Scene::_isActivated(const Entity& entity) const
{
    return _attributes[entity._id].isActivated();
}

bool Scene::_isNull(const Entity& entity) const
{
    return _attributes[entity._id].isNull();
}