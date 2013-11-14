#include "Hect.h"

using namespace hect;

EntitySystem::EntitySystem()
{
}

void EntitySystem::addEntity(Entity& entity)
{
    _entities.push_back(entity);
    onAddEntity(entity);
}

void EntitySystem::removeEntity(Entity& entity)
{
    onRemoveEntity(entity);
    _entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
}

void EntitySystem::removeAllEntities()
{
    _entities.clear();
}

const EntityAttributes& EntitySystem::requiredAttributes() const
{
    return _requiredAttributes;
}

std::vector<Entity>& EntitySystem::entities()
{
    return _entities;
}

const std::vector<Entity>& EntitySystem::entities() const
{
    return _entities;
}
