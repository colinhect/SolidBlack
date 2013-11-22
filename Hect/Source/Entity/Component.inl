namespace hect
{

template <typename T>
ComponentTypeId Component<T>::componentTypeId() const
{
    return typeId();
}

template <typename T>
ComponentTypeId Component<T>::typeId()
{
    static const ComponentTypeId typeId = BaseComponent::nextTypeId();
    return typeId;
}

}