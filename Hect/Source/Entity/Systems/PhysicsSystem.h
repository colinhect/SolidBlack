#pragma once

namespace hect
{

///
/// Simulates physical interactions of physical bodies.
class PhysicsSystem :
    public System
{
public:

    ///
    /// Constructs the system.
    PhysicsSystem();

    ///
    /// Destructor.
    ~PhysicsSystem();

    ///
    /// \copydoc System::includeEntity()
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
    void addEntity(Entity& entity);
    void removeEntity(Entity& entity);

private:
    void* _configuration;
    void* _dispatcher;
    void* _broadphase;
    void* _solver;
    void* _world;

    Vector3<> _gravity;
};

}