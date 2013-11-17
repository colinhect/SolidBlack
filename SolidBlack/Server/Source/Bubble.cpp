#include "Bubble.h"

Bubble::Bubble() :
    _scene(128)
{
    _scene.addSystem(_physicsSystem);
}

void Bubble::update(double timeStep)
{
    _physicsSystem.update(timeStep, 10);
    _scene.refresh();
}

Scene& Bubble::scene()
{
    return _scene;
}