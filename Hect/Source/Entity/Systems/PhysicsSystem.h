#pragma once

// Forward declare Bullet classes
class btCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btConstraintSolver;
class btDynamicsWorld;
class btTriangleMesh;

namespace hect
{

///
/// Simulates physical interactions of physical bodies.
class PhysicsSystem :
    public System,
    public Uncopyable
{
public:
    PhysicsSystem();

    ///
    /// \copydoc System::includesEntity()
    bool includesEntity(const Entity& entity) const;

    ///
    /// Updates all physical bodies.
    ///
    /// \param timeStep The duration of time between each update (in seconds).
    /// \param maxSubStepCount The maximum number of sub-steps.
    void update(double timeStep, unsigned maxSubStepCount);

    ///
    /// Returns the gravity.
    const Vector3<>& gravity() const;

    ///
    /// Sets the gravity.
    ///
    /// \param gravity The new gravity.
    void setGravity(const Vector3<>& gravity);

protected:
    void addEntity(const Entity& entity);
    void removeEntity(const Entity& entity);

private:
    btTriangleMesh* _toBulletMesh(Mesh* mesh);

    std::shared_ptr<btCollisionConfiguration> _configuration;
    std::shared_ptr<btCollisionDispatcher> _dispatcher;
    std::shared_ptr<btBroadphaseInterface> _broadphase;
    std::shared_ptr<btConstraintSolver> _solver;
    std::shared_ptr<btDynamicsWorld> _world;

    std::map<Mesh*, std::shared_ptr<btTriangleMesh>> _bulletMeshes;

    Vector3<> _gravity;
};

}