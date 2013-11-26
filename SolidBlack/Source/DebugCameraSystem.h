#pragma once

#include "Hect.h"
using namespace hect;

class DebugCameraSystem :
    public System
{
public:
    DebugCameraSystem(InputSystem& inputSystem);

    void update(double timeStep);

private:
    Mouse* _mouse;

    const InputAxis* _viewX;
    const InputAxis* _viewY;

    const InputAxis* _moveX;
    const InputAxis* _moveY;

    const InputAxis* _roll;
    const InputAxis* _adjustSpeed;

    double _speed;
};