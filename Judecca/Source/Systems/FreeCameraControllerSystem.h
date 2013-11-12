#pragma once

#include <Hect.h>
using namespace hect;

class FreeCameraControllerSystem :
    public EntitySystem
{
public:
    FreeCameraControllerSystem(Input& input);

    void update(double timeStep);

private:
    Mouse* _mouse;

    const InputAxis* _viewAxisX;
    const InputAxis* _viewAxisY;
    const InputAxis* _moveAxisX;
    const InputAxis* _moveAxisY;
    const InputAxis* _rollAxis;
    const InputAxis* _adjustSpeedAxis;

    double _speed;
};