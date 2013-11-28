namespace hect
{

template <typename T, typename S>
void EntitySerializer::registerComponent(const std::string& componentTypeName)
{
    if (_componentTypes.find(componentTypeName) != _componentTypes.end())
    {
        throw Error(format("Component type '%s' is already registered", componentTypeName.c_str()));
    }

    _componentTypes[componentTypeName] = T::typeId();
    _componentSerializers[T::typeId()] = BaseComponentSerializer::Ref(new S());
    _componentConstructors[T::typeId()] = [] { return std::make_shared<T>(); };
}

}