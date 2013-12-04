namespace hect
{

template <typename T>
ComponentTypeId Component<T>::typeId()
{
    static const ComponentTypeId typeId = BaseComponent::nextTypeId();
    return typeId;
}

template <typename T>
BaseComponent* Component<T>::clone() const
{
    // Invoke the copy constructor of the component
    return new T(*(T*)this);
}

template <typename T>
ComponentTypeId Component<T>::componentTypeId() const
{
    return typeId();
}

}