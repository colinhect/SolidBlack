#include "FreeCameraController.h"

FreeCameraController::FreeCameraController() :
    _mouse(nullptr),
    _viewX(nullptr),
    _viewY(nullptr),
    _moveX(nullptr),
    _moveY(nullptr),
    _roll(nullptr),
    _adjustSpeed(nullptr),
    _speed(1)
{
}

void FreeCameraController::onActivate(Entity& entity)
{
    _entity = entity;

    Input& input = entity.scene().engine().input();
    _viewX = &input.axisWithName("ViewX");
    _viewY= &input.axisWithName("ViewY");
    _moveX= &input.axisWithName("MoveX");
    _moveY= &input.axisWithName("MoveY");
    _roll= &input.axisWithName("Roll");
    _adjustSpeed= &input.axisWithName("AdjustSpeed");
}

void FreeCameraController::update(double timeStep)
{
    Transform& transform = _entity.component<Transform>();
    Camera& camera = _entity.component<Camera>();

    if (_adjustSpeed->value() >= 1)
    {
        _speed *= 2.0;
        LOG_DEBUG(format("Speed: %f", _speed));
    }
    else if (_adjustSpeed->value() <= -1)
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