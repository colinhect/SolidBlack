#include "Hect.h"

using namespace hect;

#include "Internal/Bullet.h"

PhysicsSystem::PhysicsSystem() :
    _configuration(new btDefaultCollisionConfiguration()),
    _dispatcher(new btCollisionDispatcher((btCollisionConfiguration*)_configuration)),
    _broadphase(new btDbvtBroadphase()),
    _solver(new btSequentialImpulseConstraintSolver()),
    _world(new btDiscreteDynamicsWorld(
               (btCollisionDispatcher*)_dispatcher,
               (btBroadphaseInterface*)_broadphase,
               (btConstraintSolver*)_solver,
               (btCollisionConfiguration*)_configuration
           ))
{
}

PhysicsSystem::~PhysicsSystem()
{
    delete (btDiscreteDynamicsWorld*)_world;
    delete (btSequentialImpulseConstraintSolver*)_solver;
    delete (btDbvtBroadphase*)_broadphase;
    delete (btCollisionDispatcher*)_dispatcher;
    delete (btDefaultCollisionConfiguration*)_configuration;
}

bool PhysicsSystem::includesEntity(const Entity& entity) const
{
    return entity.hasComponent<Transform>() && entity.hasComponent<RigidBody>();
}

void PhysicsSystem::update(double timeStep, unsigned maxSubStepCount)
{
    btDiscreteDynamicsWorld* world = (btDiscreteDynamicsWorld*)_world;
    world->stepSimulation(timeStep, maxSubStepCount);
}

void PhysicsSystem::addEntity(Entity& entity)
{
    System::addEntity(entity);

    RigidBody& rigidBody = entity.component<RigidBody>();

    btDiscreteDynamicsWorld* world = (btDiscreteDynamicsWorld*)_world;
    world->addRigidBody((btRigidBody*)rigidBody._bulletRigidBody);
}

void PhysicsSystem::removeEntity(Entity& entity)
{
    RigidBody& rigidBody = entity.component<RigidBody>();

    btDiscreteDynamicsWorld* world = (btDiscreteDynamicsWorld*)_world;
    world->removeRigidBody((btRigidBody*)rigidBody._bulletRigidBody);

    System::removeEntity(entity);
}