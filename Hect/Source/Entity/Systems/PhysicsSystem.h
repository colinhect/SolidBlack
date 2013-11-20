#pragma once

namespace hect
{

class PhysicsSystem :
    public EntitySystem
{
public:
    PhysicsSystem();
    ~PhysicsSystem();

    ///
    /// Updates all physical bodies.
    ///
    /// \param timeStep The time step.
    /// \param maxSubStepCount The maximum number of sub steps.
    void update(double timeStep, unsigned maxSubStepCount);

protected:

    ///
    /// \copydoc EntitySystem::onAddEntity()
    void onAddEntity(Entity& entity);

    ///
    /// \copydoc EntitySystem::onRemoveEntity()
    void onRemoveEntity(Entity& entity);

private:
    void* _configuration;
    void* _dispatcher;
    void* _broadphase;
    void* _solver;
    void* _world;
};

}