#include "Hect.h"

using namespace hect;

Entity::Entity() :
    _scene(nullptr),
    _id(0)
{
}

Scene& Entity::scene()
{
    assert(_scene);
    return *_scene;
}

void Entity::destroy()
{
    assert(_scene);
    _scene->_destroyEntity(*this);
}

void Entity::activate()
{
    assert(_scene);
    _scene->_activateEntity(*this);
}

void Entity::deactivate()
{
    assert(_scene);
    _scene->_deactivateEntity(*this);
}

bool Entity::isActivated() const
{
    assert(_scene);
    return _scene->_isActivated(*this);
}

bool Entity::isNull() const
{
    return !_scene || _scene->_isNull(*this);
}

bool Entity::operator==(const Entity& entity) const
{
    return _scene == entity._scene &&_id == entity._id;
}

Entity::Entity(Scene& scene, Id id) :
    _scene(&scene),
    _id(id)
{
}