#include "Hect.h"

using namespace hect;

#include "Internal/Bullet.h"

RigidBody::RigidBody(Transform& transform, double mass, const Box<>& collisionBox) :
    _transform(&transform),
    _mass(mass),
    _bulletShape(nullptr),
    _bulletRigidBody(nullptr)
{
    btBoxShape* shape = new btBoxShape(convertToBullet(collisionBox.scale()));

    btVector3 localInertia(0, 0, 0);
    if (_mass != 0.0)
    {
        shape->calculateLocalInertia(_mass, localInertia);
    }

    btMotionState* motionState = new btDefaultMotionState(convertToBullet(transform));
    btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, shape, localInertia);
    btRigidBody* rigidBody = new btRigidBody(info);

    _bulletShape = shape;
    _bulletRigidBody = rigidBody;
}

RigidBody::~RigidBody()
{
    btRigidBody* rigidBody = (btRigidBody*)_bulletRigidBody;
    delete rigidBody->getMotionState();
    delete rigidBody->getCollisionShape();
    delete rigidBody;

    _bulletShape = nullptr;
    _bulletRigidBody = nullptr;
}