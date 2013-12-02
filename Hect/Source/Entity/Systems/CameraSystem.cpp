#include "Hect.h"

using namespace hect;

bool CameraSystem::includesEntity(const Entity& entity) const
{
    return entity.hasComponent<Transform>() && entity.hasComponent<Camera>();
}

bool CameraSystem::hasCamera() const
{
    return !entities().empty();
}

Camera& CameraSystem::camera()
{
    assert(hasCamera());
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
