#include "Hect.h"

using namespace hect;

BehaviorSystem::BehaviorSystem()
{
    requireComponent<Behavior>();
}

void BehaviorSystem::update(double timeStep)
{
    // Pre-update
    for (Entity& entity : entities())
    {
        Behavior& behavior = entity.component<Behavior>();
        behavior.preUpdate(timeStep);
    }

    // Update
    for (Entity& entity : entities())
    {
        Behavior& behavior = entity.component<Behavior>();
        behavior.update(timeStep);
    }

    // Post-update
    for (Entity& entity : entities())
    {
        Behavior& behavior = entity.component<Behavior>();
        behavior.postUpdate(timeStep);
    }
}
