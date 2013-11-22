#include "Hect.h"

using namespace hect;

System::System()
{
}

void System::addEntity(Entity& entity)
{
    _entities.push_back(entity);
    onAddEntity(entity);
}

void System::removeEntity(Entity& entity)
{
    onRemoveEntity(entity);
    _entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
}

void System::removeAllEntities()
{
    for (Entity& entity : _entities)
    {
        onRemoveEntity(entity);
    }

    _entities.clear();
}

const EntityAttributes& System::requiredAttributes() const
{
    return _requiredAttributes;
}

void System::onAddEntity(Entity& entity)
{
    entity;
}

void System::onRemoveEntity(Entity& entity)
{
    entity;
}

std::vector<Entity>& System::entities()
{
    return _entities;
}

const std::vector<Entity>& System::entities() const
{
    return _entities;
}
