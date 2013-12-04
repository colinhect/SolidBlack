namespace hect
{

template <typename T>
bool Entity::hasComponent() const
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }

    return _scene->_hasComponent<T>(*this);
}

template <typename T>
T& Entity::addComponent()
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }

    return _scene->_addComponent<T>(*this, std::make_shared<T>());
}

template <typename T>
T& Entity::component()
{
    if (!_scene)
    {
        throw Error("Entity is null");
    }

    return _scene->_component<T>(*this);
}

}