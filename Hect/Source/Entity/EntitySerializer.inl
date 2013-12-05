namespace hect
{

template <typename T, typename S>
void EntitySerializer::registerComponent(const std::string& componentTypeName)
{
    ComponentTypeId typeId = T::typeId();

    // Check that the type name is not already registered
    if (_componentTypeIds.find(componentTypeName) != _componentTypeIds.end())
    {
        throw Error(format("Component type '%s' is already registered", componentTypeName.c_str()));
    }

    // Check that the type id is not already registered
    if (_componentSerializers.find(typeId) != _componentSerializers.end())
    {
        throw Error(format("Component type id '%d' is already registered", typeId));
    }

    // Map the type name to the type id
    _componentTypeIds[componentTypeName] = typeId;

    // Map the type id to the type name
    _componentTypeNames[typeId] = componentTypeName;

    // Create the serializer
    _componentSerializers[typeId] = BaseComponentSerializer::Ref(new S());

    // Create the constructor
    _componentConstructors[typeId] = [] { return new T(); };
}

}