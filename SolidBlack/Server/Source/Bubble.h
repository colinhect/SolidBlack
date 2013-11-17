#pragma once

#include <Hect.h>
using namespace hect;

class Bubble
{
public:
    typedef std::shared_ptr<Bubble> Ref;
    typedef std::vector<Ref> RefArray;

    Bubble();

    void update(double timeStep);

    Scene& scene();

private:
    PhysicsSystem _physicsSystem;

    Scene _scene;
};