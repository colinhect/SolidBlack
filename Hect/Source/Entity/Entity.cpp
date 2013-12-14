#include "Hect.h"

using namespace hect;

Entity::Entity() :
    _scene(nullptr),
    _id(0)
{
}

Scene& Entity::scene() const
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }

    return *_scene;
}

Entity::Id Entity::id() const
{
    return _id;
}

void Entity::save(DataValue& dataValue)
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }

    _scene->_entitySerializer.save(*this, dataValue);
}

void Entity::save(WriteStream& stream)
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }

    _scene->_entitySerializer.save(*this, stream);
}

void Entity::load(const DataValue& dataValue, AssetCache& assetCache)
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }
    else if (isActivated())
    {
        throw Error("Entity is activated");
    }

    _scene->_entitySerializer.load(*this, dataValue, assetCache);
}

void Entity::load(ReadStream& stream, AssetCache& assetCache)
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }
    else if (isActivated())
    {
        throw Error("Entity is activated");
    }

    _scene->_entitySerializer.load(*this, stream, assetCache);
}

void Entity::destroy()
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }

    _scene->_destroyEntity(*this);
}

Entity Entity::clone() const
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }

    return _scene->_cloneEntity(*this);
}

void Entity::activate()
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }

    _scene->_activateEntity(*this);
}

bool Entity::isActivated() const
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }

    return _scene->_isActivated(*this);
}

bool Entity::isNull() const
{
    return !_scene || _scene->_isNull(*this);
}

void Entity::addComponent(BaseComponent* component)
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }

    _scene->_addComponentWithoutReturn(*this, BaseComponent::Ref(component));
}

std::vector<BaseComponent*> Entity::components() const
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }

    std::vector<BaseComponent*> resultingComponents;
    auto& components = _scene->_entityComponents[_id];
    for (auto& pair : components)
    {
        resultingComponents.push_back(pair.second.get());
    }

    return resultingComponents;
}

Entity::operator bool() const
{
    return !isNull();
}

bool Entity::operator==(const Entity& entity) const
{
    return _scene == entity._scene && _id == entity._id;
}

bool Entity::operator!=(const Entity& entity) const
{
    return _scene != entity._scene || _id != entity._id;
}

Entity::Entity(Scene& scene, Id id) :
    _scene(&scene),
    _id(id)
{
}