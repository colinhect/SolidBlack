#include "FreeCameraControllerSystem.h"

#include "Components/FreeCameraController.h"

FreeCameraControllerSystem::FreeCameraControllerSystem(Input& input) :
    _mouse(&input.mouse()),
    _viewAxisX(&input.axisWithName("ViewX")),
    _viewAxisY(&input.axisWithName("ViewY")),
    _moveAxisX(&input.axisWithName("MoveX")),
    _moveAxisY(&input.axisWithName("MoveY")),
    _rollAxis(&input.axisWithName("Roll")),
    _adjustSpeedAxis(&input.axisWithName("AdjustSpeed")),
    _speed(1)
{
    requireComponent<Transform>();
    requireComponent<Camera>();
    requireComponent<FreeCameraController>();
}

void FreeCameraControllerSystem::update(double timeStep)
{
    if (entities().size() == 0 || !_mouse->isCursorLocked())
    {
        return;
    }

    Entity& entity = entities().back();

    Transform& transform = entity.component<Transform>();
    Camera& camera = entity.component<Camera>();

    if (_adjustSpeedAxis)
    {
        if (_adjustSpeedAxis->value() >= 1.0f)
        {
            _speed *= 2.0;
            LOG_DEBUG(format("Speed: %f", _speed));
        }
        else if (_adjustSpeedAxis->value() <= -1.0f)
        {
            _speed /= 2.0;
            LOG_DEBUG(format("Speed: %f", _speed));
        }
    }

    if (_viewAxisX)
    {
        transform.rotateGlobal(camera.up(), Angle<>::fromRadians(_viewAxisX->value() * 50.0 * timeStep));
    }

    if (_viewAxisY)
    {
        transform.rotateGlobal(camera.right(), Angle<>::fromRadians(_viewAxisY->value() * -50.0 * timeStep));
    }

    if (_rollAxis)
    {
        transform.rotateGlobal(camera.front(),  Angle<>::fromRadians(_rollAxis->value() * -2.0 * timeStep));
    }

    if (_moveAxisX)
    {
        transform.translate(camera.right() * _moveAxisX->value() * _speed * timeStep);
    }

    if (_moveAxisY)
    {
        transform.translate(camera.front() * _moveAxisY->value() * _speed * timeStep);
    }
}