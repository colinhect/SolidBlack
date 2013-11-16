#pragma once

namespace hect
{

class PhysicsSystem :
    public EntitySystem
{
public:
    PhysicsSystem();
    ~PhysicsSystem();

    void update(double timeStep, unsigned maxSubSteps);

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