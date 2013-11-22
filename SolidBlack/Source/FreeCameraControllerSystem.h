#pragma once

#include <Hect.h>
using namespace hect;

class FreeCameraControllerSystem :
    public System
{
public:
    FreeCameraControllerSystem(Input& input);

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