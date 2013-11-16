#pragma once

namespace hect
{

class RigidBody :
    public EntityComponent<RigidBody>
{
    friend class PhysicsSystem;
public:
    RigidBody(Transform& transform, double mass, const Box<>& collisionBox);
    ~RigidBody();

private:
    Transform* _transform;
    double _mass;

    void* _bulletShape;
    void* _bulletRigidBody;
};

}