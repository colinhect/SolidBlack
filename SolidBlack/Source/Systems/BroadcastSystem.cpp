#include "SolidBlack.h"

BroadcastSystem::BroadcastSystem(Scene& scene) :
    _scene(&scene)
{
}

bool BroadcastSystem::includesEntity(const Entity& entity) const
{
    return entity.hasComponent<Broadcast>();
}

void BroadcastSystem::addEntity(Entity& entity)
{
    System::addEntity(entity);
}

void BroadcastSystem::removeEntity(Entity& entity)
{
    System::removeEntity(entity);
}