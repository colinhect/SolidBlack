#pragma once

class Bubble :
    public Uncopyable
{
public:

    typedef std::shared_ptr<Bubble> Ref;

    Bubble(AssetCache& assetCache);
    ~Bubble();

    void update(double timeStep);

private:
    PhysicsSystem _physicsSystem;

    Scene _scene;

    Entity _testRigidBody;
};