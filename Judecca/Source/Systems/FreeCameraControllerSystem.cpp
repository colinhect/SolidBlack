#include "FreeCameraControllerSystem.h"

#include "Components/FreeCameraController.h"

FreeCameraControllerSystem::FreeCameraControllerSystem(Input& input) :
    _mouse(&input.mouse()),
    _viewX(&input.axisWithName("ViewX")),
    _viewY(&input.axisWithName("ViewY")),
    _moveX(&input.axisWithName("MoveX")),
    _moveY(&input.axisWithName("MoveY")),
    _roll(&input.axisWithName("Roll")),
    _adjustSpeed(&input.axisWithName("AdjustSpeed")),
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

    if (_adjustSpeed->value() >= 1.0f)
    {
        _speed *= 2.0;
        LOG_DEBUG(format("Speed: %f", _speed));
    }
    else if (_adjustSpeed->value() <= -1.0f)
    {
        _speed /= 2.0;
        LOG_DEBUG(format("Speed: %f", _speed));
    }

    transform.rotateGlobal(camera.up(), Angle<>::fromRadians(_viewX->value() * 50.0 * timeStep));
    transform.rotateGlobal(camera.right(), Angle<>::fromRadians(_viewY->value() * -50.0 * timeStep));
    transform.rotateGlobal(camera.front(),  Angle<>::fromRadians(_roll->value() * -2.0 * timeStep));
    transform.translate(camera.right() * _moveX->value() * _speed * timeStep);
    transform.translate(camera.front() * _moveY->value() * _speed * timeStep);
}