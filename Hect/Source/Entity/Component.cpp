#include "Hect.h"

using namespace hect;

ComponentTypeId BaseComponent::nextTypeId()
{
    static ComponentTypeId nextTypeId = 0;
    return nextTypeId++;
}

BaseComponent::BaseComponent() :
    _scene(nullptr),
    _entityId(0)
{
}

bool BaseComponent::hasEntity() const
{
    return _scene != nullptr;
}

Entity BaseComponent::entity() const
{
    return Entity(*_scene, _entityId);
}

void BaseComponent::_activate(Entity& entity)
{
    _scene = &entity.scene();
    _entityId = entity.id();
}

void BaseComponent::_deactivate(Entity& entity)
{
    _scene = nullptr;
    _entityId = 0;
}