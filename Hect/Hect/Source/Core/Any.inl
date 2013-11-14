namespace hect
{

template <typename T>
Any::Any(const T& value) :
    _container(new ContainerValue<T>(value))
{
}

template <typename T>
Any& Any::operator=(const T& value)
{
    if (_container)
    {
        delete _container;
    }

    _container = new ContainerValue<T>(value);

    return *this;
}

template <typename T>
bool Any::isType() const
{
    if (_container)
    {
        return dynamic_cast<ContainerValue<T>*>(_container) != nullptr;
    }
    else
    {
        return false;
    }
}

template <typename T>
T& Any::as() const
{
    auto containerValue = dynamic_cast<ContainerValue<T>*>(_container);

    if (!containerValue)
    {
        throw Error("Invalid type");
    }

    return containerValue->held;
}

template <typename T>
Any::ContainerValue<T>::ContainerValue(const T& value) :
    held(value)
{
}

template <typename T>
Any::Container* Any::ContainerValue<T>::clone() const
{
    return new ContainerValue(held);
}

}