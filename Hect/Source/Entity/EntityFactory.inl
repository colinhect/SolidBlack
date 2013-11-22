namespace hect
{

template <typename ComponentType, typename SerializerType>
void EntityFactory::registerSerializer(const std::string& componentTypeName)
{
    if (_componentTypes.find(componentTypeName) != _componentTypes.end())
    {
        throw Error(format("Component type '%s' already has a serializer registered", componentTypeName.c_str()));
    }

    _componentTypes[componentTypeName] = ComponentType::type();
    _componentSerializers[ComponentType::type()] = std::shared_ptr<BaseComponentSerializer>(new SerializerType());
    _componentConstructors[ComponentType::type()] = [] { return std::make_shared<ComponentType>(); };
}

}