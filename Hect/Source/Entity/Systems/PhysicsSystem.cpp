#include "Hect.h"

using namespace hect;

#include "Internal/Bullet.h"

PhysicsSystem::PhysicsSystem() :
    _configuration(new btDefaultCollisionConfiguration()),
    _dispatcher(new btCollisionDispatcher(_configuration.get())),
    _broadphase(new btDbvtBroadphase()),
    _solver(new btSequentialImpulseConstraintSolver()),
    _world(new btDiscreteDynamicsWorld(_dispatcher.get(), _broadphase.get(), _solver.get(), _configuration.get()))
{
    setGravity(Vector3<>::zero());
}

bool PhysicsSystem::includesEntity(const Entity& entity) const
{
    return entity.hasComponent<Transform>() && entity.hasComponent<RigidBody>();
}

void PhysicsSystem::update(double timeStep, unsigned maxSubStepCount)
{
    // Update the dynamics world
    _world->stepSimulation(timeStep, maxSubStepCount);

    // Update the transform for all entities with a rigid body
    for (Entity& entity : entities())
    {
        RigidBody& rigidBody = entity.component<RigidBody>();
        Transform& transform = entity.component<Transform>();
        transform = convertFromBullet(rigidBody._rigidBody->getWorldTransform());
    }
}

const Vector3<>& PhysicsSystem::gravity() const
{
    return _gravity;
}

void PhysicsSystem::setGravity(const Vector3<>& gravity)
{
    _gravity = gravity;
    _world->setGravity(convertToBullet(gravity));
}

void PhysicsSystem::addEntity(Entity& entity)
{
    System::addEntity(entity);

    Transform& transform = entity.component<Transform>();
    RigidBody& rigidBody = entity.component<RigidBody>();
    Mesh* mesh = rigidBody.mesh().get();
    
    rigidBody._collisionShape.reset(new btConvexTriangleMeshShape(_toBulletMesh(mesh)));

    btScalar mass = rigidBody.mass();
    btVector3 localInertia(0, 0, 0);
    if (mass != 0.0)
    {
        rigidBody._collisionShape->calculateLocalInertia(mass, localInertia);
    }

    btVector3 linearVelocity = convertToBullet(rigidBody.linearVelocity());
    btVector3 angularVelocity = convertToBullet(rigidBody.angularVelocity());

    rigidBody._motionState.reset(new btDefaultMotionState(convertToBullet(transform)));
    btRigidBody::btRigidBodyConstructionInfo info(mass, rigidBody._motionState.get(), rigidBody._collisionShape.get(), localInertia);
    rigidBody._rigidBody.reset(new btRigidBody(info));
    rigidBody._rigidBody->setSleepingThresholds(0, 0);
    rigidBody._rigidBody->setLinearVelocity(linearVelocity);
    rigidBody._rigidBody->setAngularVelocity(angularVelocity);

    _world->addRigidBody(rigidBody._rigidBody.get());
}

void PhysicsSystem::removeEntity(Entity& entity)
{
    RigidBody& rigidBody = entity.component<RigidBody>();
    _world->removeRigidBody(rigidBody._rigidBody.get());

    System::removeEntity(entity);
}

btTriangleMesh* PhysicsSystem::_toBulletMesh(Mesh* mesh)
{
    auto it = _bulletMeshes.find(mesh);
    if (it != _bulletMeshes.end())
    {
        // The Bullet mesh was already created
        return (*it).second.get();
    }
    else
    {
        // Create a Bullet mesh from the mesh and save it to be looked up later
        btTriangleMesh* bulletMesh = convertToBullet(*mesh);
        _bulletMeshes[mesh] = std::shared_ptr<btTriangleMesh>(bulletMesh);
        return bulletMesh;
    }
}