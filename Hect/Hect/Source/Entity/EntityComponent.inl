namespace hect
{

template <typename T>
EntityComponentType EntityComponent<T>::componentType() const
{
    return type();
}

template <typename T>
EntityComponentType EntityComponent<T>::type()
{
    static const EntityComponentType type = BaseComponent::nextType();
    return type;
}

}