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
    /// \param timeStep The time between last frame and this one.
    /// \param maxSubStepCount The maximum number of sub-steps.
    void update(double timeStep, unsigned maxSubStepCount);

protected:

    ///
    /// \copydoc System::onAddEntity()
    void onAddEntity(Entity& entity);

    ///
    /// \copydoc System::onRemoveEntity()
    void onRemoveEntity(Entity& entity);

private:
    void* _configuration;
    void* _dispatcher;
    void* _broadphase;
    void* _solver;
    void* _world;
};

}