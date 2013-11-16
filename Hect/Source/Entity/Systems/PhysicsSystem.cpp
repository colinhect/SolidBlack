#include "Hect.h"

using namespace hect;

PhysicsSystem::PhysicsSystem()
{
    requireComponent<Transform>();
    requireComponent<RigidBody>();
}