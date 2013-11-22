namespace hect
{

template <typename T>
ComponentType Component<T>::componentType() const
{
    return type();
}

template <typename T>
ComponentType Component<T>::type()
{
    static const ComponentType type = BaseComponent::nextType();
    return type;
}

}