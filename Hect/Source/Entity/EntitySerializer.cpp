#include "Hect.h"

using namespace hect;

EntitySerializer::EntitySerializer()
{
    // Register all hect components
    registerComponent<Camera, CameraSerializer>("Camera");
    registerComponent<AmbientLight, AmbientLightSerializer>("AmbientLight");
    registerComponent<DirectionalLight, DirectionalLightSerializer>("DirectionalLight");
    registerComponent<Geometry, GeometrySerializer>("Geometry");
    registerComponent<Transform, TransformSerializer>("Transform");
    registerComponent<RigidBody, RigidBodySerializer>("RigidBody");
}

void EntitySerializer::save(Entity& entity, DataValue& dataValue)
{
    if (!entity)
    {
        throw Error("Entity is null");
    }

    dataValue = DataValue(DataValueType::Object);

    // For each component in the entity
    for (BaseComponent* component : entity.components())
    {
        ComponentTypeId typeId = component->componentTypeId();
        const std::string& typeName = _typeName(typeId);
        const BaseComponentSerializer& serializer = _serializer(typeId);

        // Serialize
        DataValueWriter writer;
        serializer.save(component, writer);

        // Save the resulting data value from the writer to the member data
        // value
        dataValue.addMember(typeName, writer.currentDataValue());
    }
}

void EntitySerializer::save(Entity& entity, WriteStream& stream)
{
    if (!entity)
    {
        throw Error("Entity is null");
    }

    // Write the number of components as a byte
    std::vector<BaseComponent*> components = entity.components();
    stream.writeByte((uint8_t)components.size());

    // For each component in the entity
    for (BaseComponent* component : components)
    {
        ComponentTypeId typeId = component->componentTypeId();
        const BaseComponentSerializer& serializer = _serializer(typeId);

        // Write the type id as a byte
        stream.writeByte((uint8_t)typeId);

        // Serialize
        BinaryDataWriter writer(stream);
        serializer.save(component, writer);
    }
}

void EntitySerializer::load(Entity& entity, const DataValue& dataValue, AssetCache& assetCache)
{
    if (!entity)
    {
        throw Error("Entity is null");
    }

    // For each component type name
    for (const std::string& typeName : dataValue.memberNames())
    {
        ComponentTypeId typeId = _typeId(typeName);
        const BaseComponentSerializer& serializer = _serializer(typeId);

        // Create component
        BaseComponent* component = _constructComponent(typeId);

        // Deserialize
        DataValueReader reader(dataValue[typeName]);
        serializer.load(component, reader, assetCache);

        // Add component
        entity.addComponent(component);
    }
}

void EntitySerializer::load(Entity& entity, ReadStream& stream, AssetCache& assetCache)
{
    if (!entity)
    {
        throw Error("Entity is null");
    }

    // Read the number of components
    uint8_t componentCount = stream.readByte();

    // For each component
    for (uint8_t i = 0; i < componentCount; ++i)
    {
        ComponentTypeId typeId = stream.readByte();
        const BaseComponentSerializer& serializer = _serializer(typeId);

        // Create component
        BaseComponent* component = _constructComponent(typeId);

        // Deserialize
        BinaryDataReader reader(stream);
        serializer.load(component, reader, assetCache);

        // Add component
        entity.addComponent(component);
    }
}

ComponentTypeId EntitySerializer::_typeId(const std::string& typeName) const
{
    auto it = _componentTypeIds.find(typeName);
    if (it == _componentTypeIds.end())
    {
        throw Error(format("No serializer registered for component type name '%s'", typeName.c_str()));
    }
    return (*it).second;
}

const std::string& EntitySerializer::_typeName(ComponentTypeId typeId) const
{
    auto it = _componentTypeNames.find(typeId);
    if (it == _componentTypeNames.end())
    {
        throw Error(format("No serializer registered for component type id '%d'", typeId));
    }
    return (*it).second;
}

const BaseComponentSerializer& EntitySerializer::_serializer(ComponentTypeId typeId) const
{
    auto it = _componentSerializers.find(typeId);
    if (it == _componentSerializers.end())
    {
        throw Error(format("No serializer registered for component type id '%d'", typeId));
    }
    return *(*it).second;
}

BaseComponent* EntitySerializer::_constructComponent(ComponentTypeId typeId) const
{
    auto it = _componentConstructors.find(typeId);
    if (it == _componentConstructors.end())
    {
        throw Error(format("No serializer registered for component type id '%d'", typeId));
    }
    return (*it).second();
}