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

BaseComponent::BaseComponent(const BaseComponent& component) :
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