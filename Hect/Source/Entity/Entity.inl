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

template <typename T, typename A0>
T& Entity::addComponent(A0&& a0)
{
    assert(_id);
    assert(_scene);
    return _scene->_addComponent<T>(*this, std::make_shared<T>(a0));
}

template <typename T, typename A0, typename A1>
T& Entity::addComponent(A0&& a0, A1&& a1)
{
    assert(_id);
    assert(_scene);
    return _scene->_addComponent<T>(*this, std::make_shared<T>(a0, a1));
}

template <typename T, typename A0, typename A1, typename A2>
T& Entity::addComponent(A0&& a0, A1&& a1, A2&& a2)
{
    assert(_id);
    assert(_scene);
    return _scene->_addComponent<T>(*this, std::make_shared<T>(a0, a1, a2));
}

template <typename T, typename A0, typename A1, typename A2, typename A3>
T& Entity::addComponent(A0&& a0, A1&& a1, A2&& a2, A3&& a3)
{
    assert(_id);
    assert(_scene);
    return _scene->_addComponent<T>(*this, std::make_shared<T>(a0, a1, a2, a3));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
T& Entity::addComponent(A0&& a0, A1&& a1, A2&& a2, A3&& a3, A4&& a4)
{
    assert(_id);
    assert(_scene);
    return _scene->_addComponent<T>(*this, std::make_shared<T>(a0, a1, a2, a3, a4));
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