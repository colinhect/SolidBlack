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
    setGravity(Vector3<>::zero());
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

    // Update the transform for all entities with a rigid body
    for (Entity& entity : entities())
    {
        Transform& transform = entity.component<Transform>();
        RigidBody& rigidBody = entity.component<RigidBody>();

        btRigidBody* bulletRigidBody = (btRigidBody*)rigidBody._bulletRigidBody;
        transform = convertFromBullet(bulletRigidBody->getWorldTransform());
    }
}

const Vector3<>& PhysicsSystem::gravity() const
{
    return _gravity;
}

void PhysicsSystem::setGravity(const Vector3<>& gravity)
{
    _gravity = gravity;
    ((btDiscreteDynamicsWorld*)_world)->setGravity(convertToBullet(gravity));
}

void PhysicsSystem::addEntity(Entity& entity)
{
    System::addEntity(entity);

    Transform& transform = entity.component<Transform>();
    RigidBody& rigidBody = entity.component<RigidBody>();

    btTriangleMesh* mesh = convertToBullet(*rigidBody.mesh().get());
    rigidBody._bulletMesh = mesh;

    btCollisionShape* shape = new btConvexTriangleMeshShape(mesh);

    btScalar mass = rigidBody.mass();
    btVector3 localInertia(0, 0, 0);
    if (mass != 0.0)
    {
        shape->calculateLocalInertia(mass, localInertia);
    }

    btMotionState* motionState = new btDefaultMotionState(convertToBullet(transform));
    btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, shape, localInertia);
    btRigidBody* bulletRigidBody = new btRigidBody(info);
    bulletRigidBody->setSleepingThresholds(0, 0);
    bulletRigidBody->setLinearVelocity(convertToBullet(rigidBody.linearVelocity()));
    bulletRigidBody->setAngularVelocity(convertToBullet(rigidBody.angularVelocity()));

    rigidBody._bulletRigidBody = bulletRigidBody;

    btDiscreteDynamicsWorld* world = (btDiscreteDynamicsWorld*)_world;
    world->addRigidBody(bulletRigidBody);
}

void PhysicsSystem::removeEntity(Entity& entity)
{
    RigidBody& rigidBody = entity.component<RigidBody>();

    btDiscreteDynamicsWorld* world = (btDiscreteDynamicsWorld*)_world;
    world->removeRigidBody((btRigidBody*)rigidBody._bulletRigidBody);

    System::removeEntity(entity);
}