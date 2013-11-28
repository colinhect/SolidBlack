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
    ~PhysicsSystem();

    ///
    /// Updates all physical bodies.
    ///
    /// \param timeStep The duration of time between each update (in seconds).
    /// \param maxSubStepCount The maximum number of sub-steps.
    void update(double timeStep, unsigned maxSubStepCount);

protected:
    void addEntity(Entity& entity);
    void removeEntity(Entity& entity);

private:
    void* _configuration;
    void* _dispatcher;
    void* _broadphase;
    void* _solver;
    void* _world;
};

}