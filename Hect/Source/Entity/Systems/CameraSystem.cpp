#include "Hect.h"

using namespace hect;

CameraSystem::CameraSystem()
{
    requireComponent<Transform>();
    requireComponent<Camera>();
}

bool CameraSystem::hasCamera() const
{
    return !entities().empty();
}

Camera& CameraSystem::camera()
{
    assert(!entities().empty());
    return entities().back().component<Camera>();
}

void CameraSystem::update()
{
    for (Entity& entity : entities())
    {
        Camera& camera = entity.component<Camera>();
        Transform& transform = entity.component<Transform>();
        camera.transformTo(transform);
    }
}
