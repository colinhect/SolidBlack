#include "DebugCameraSystem.h"

#include "DebugCamera.h"

DebugCameraSystem::DebugCameraSystem(InputSystem& inputSystem) :
    _mouse(&inputSystem.mouse()),
    _viewX(&inputSystem.axisWithName("viewX")),
    _viewY(&inputSystem.axisWithName("viewY")),
    _moveX(&inputSystem.axisWithName("moveX")),
    _moveY(&inputSystem.axisWithName("moveY")),
    _roll(&inputSystem.axisWithName("roll")),
    _adjustSpeed(&inputSystem.axisWithName("adjustSpeed")),
    _speed(1)
{
}

bool DebugCameraSystem::includesEntity(const Entity& entity) const
{
    return entity.hasComponent<Transform>() && entity.hasComponent<Camera>() && entity.hasComponent<DebugCamera>();
}

void DebugCameraSystem::update(double timeStep)
{
    if (entities().size() == 0)
    {
        return;
    }

    Entity& entity = entities().front();

    Transform& transform = entity.component<Transform>();
    Camera& camera = entity.component<Camera>();

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