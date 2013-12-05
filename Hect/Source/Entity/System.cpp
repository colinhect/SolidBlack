#include "Hect.h"

using namespace hect;

void System::addEntity(Entity& entity)
{
    _entities.push_back(entity);
}

void System::removeEntity(Entity& entity)
{
    // Possible performance issue
    _entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
}

void System::removeAllEntities()
{
    // Possible performance issue
    while (!_entities.empty())
    {
        removeEntity(_entities.back());
    }
}

bool System::includesEntity(const Entity& entity) const
{
    return true;
}

std::vector<Entity>& System::entities()
{
    return _entities;
}

const std::vector<Entity>& System::entities() const
{
    return _entities;
}
