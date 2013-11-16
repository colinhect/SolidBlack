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
    requireComponent<Transform>();
    requireComponent<RigidBody>();
}

PhysicsSystem::~PhysicsSystem()
{
    delete (btDiscreteDynamicsWorld*)_world;
    delete (btSequentialImpulseConstraintSolver*)_solver;
    delete (btDbvtBroadphase*)_broadphase;
    delete (btCollisionDispatcher*)_dispatcher;
    delete (btDefaultCollisionConfiguration*)_configuration;
}

void PhysicsSystem::update(double timeStep, unsigned maxSubSteps)
{
    btDiscreteDynamicsWorld* world = (btDiscreteDynamicsWorld*)_world;
    world->stepSimulation(timeStep, maxSubSteps);
}

void PhysicsSystem::onAddEntity(Entity& entity)
{
    RigidBody& rigidBody = entity.component<RigidBody>();

    btDiscreteDynamicsWorld* world = (btDiscreteDynamicsWorld*)_world;
    world->addRigidBody((btRigidBody*)rigidBody._bulletRigidBody);
}

void PhysicsSystem::onRemoveEntity(Entity& entity)
{
    RigidBody& rigidBody = entity.component<RigidBody>();

    btDiscreteDynamicsWorld* world = (btDiscreteDynamicsWorld*)_world;
    world->removeRigidBody((btRigidBody*)rigidBody._bulletRigidBody);
}