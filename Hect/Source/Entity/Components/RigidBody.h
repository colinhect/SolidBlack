#pragma once

// Forward declare Bullet classes
class btRigidBody;
class btMotionState;
class btCollisionShape;

namespace hect
{

///
/// A simulated physical body.
class RigidBody :
    public Component<RigidBody>
{
    friend class PhysicsSystem;
public:
    RigidBody();

    ///
    /// Returns the mass.
    double mass() const;

    ///
    /// Sets the mass.
    ///
    /// \param mass The new mass.
    void setMass(double mass);

    ///
    /// Returns the linear velocity.
    const Vector3<>& linearVelocity() const;

    ///
    /// Sets the linear velocity.
    ///
    /// \param linearVelocity The new linear velocity.
    void setLinearVelocity(const Vector3<>& linearVelocity);

    ///
    /// Returns the angular velocity.
    const Vector3<>& angularVelocity() const;

    ///
    /// Sets the angular velocity.
    ///
    /// \param angularVelocity The new angular velocity.
    void setAngularVelocity(const Vector3<>& angularVelocity);

    ///
    /// Returns the mesh.
    AssetHandle<Mesh>& mesh();

    ///
    /// Returns the mesh.
    const AssetHandle<Mesh>& mesh() const;

    ///
    /// Sets the mesh.
    ///
    /// \param mesh The new mesh.
    void setMesh(const AssetHandle<Mesh>& mesh);

private:
    double _mass;
    mutable Vector3<> _linearVelocity;
    mutable Vector3<> _angularVelocity;
    AssetHandle<Mesh> _mesh;
    
    std::shared_ptr<btRigidBody> _rigidBody;
    std::shared_ptr<btMotionState> _motionState;
    std::shared_ptr<btCollisionShape> _collisionShape;
};

///
/// Serializer for RigidBody.
class RigidBodySerializer :
    public ComponentSerializer<RigidBody>
{
public:

    ///
    /// See BaseComponentSerializer::save()
    void save(const RigidBody& rigidBody, DataWriter& writer) const;

    ///
    /// See BaseComponentSerializer::load()
    void load(RigidBody& rigidBody, DataReader& reader, AssetCache& assetCache) const;
};

}