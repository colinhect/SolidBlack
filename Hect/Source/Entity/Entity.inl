namespace hect
{

template <typename T>
bool Entity::hasComponent() const
{
    assert(_id);
    assert(_scene);
    return _scene->_hasComponent<T>(*this);
}

template <typename T>
T& Entity::addComponent()
{
    assert(_id);
    assert(_scene);
    return _scene->_addComponent<T>(*this, std::make_shared<T>());
}

template <typename T>
void Entity::removeComponent()
{
    assert(_id);
    assert(_scene);
    return _scene->_removeComponent<T>(*this);
}

template <typename T>
T& Entity::component()
{
    assert(_id);
    assert(_scene);
    return _scene->_component<T>(*this);
}

}