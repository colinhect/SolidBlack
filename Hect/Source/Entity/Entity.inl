namespace hect
{

template <typename T>
bool Entity::hasComponent() const
{
    assert(_scene);
    return _scene->_hasComponent<T>(*this);
}

template <typename T>
T& Entity::addComponent()
{
    assert(_scene);
    return _scene->_addComponent<T>(*this, std::make_shared<T>());
}

template <typename T>
T& Entity::component()
{
    assert(_scene);
    return _scene->_component<T>(*this);
}

}