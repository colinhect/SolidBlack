#pragma once

#include "Components/PlayerCamera.h"

class PlayerCameraSystem :
    public System
{
public:
    PlayerCameraSystem(InputSystem& inputSystem);

    bool includesEntity(const Entity& entity) const;

    void update(double timeStep);

private:
    Mouse* _mouse;

    const InputAxis* _viewX;
    const InputAxis* _viewY;

    const InputAxis* _moveX;
    const InputAxis* _moveY;

    const InputAxis* _roll;

    double _speed;
};