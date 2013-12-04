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
}

void EntitySerializer::save(Entity& entity, DataValue& dataValue)
{
    if (!entity)
    {
        throw Error("Entity is null");
    }
    Scene* scene = entity._scene;
    Entity::Id id = entity._id;

    DataValue::Object members;

    auto& components = scene->_entityComponents[id];
    for (auto& pair : components)
    {
        BaseComponent* component = pair.second.get();
        ComponentTypeId typeId = component->componentTypeId();
        const std::string& typeName = _typeName(typeId);
        const BaseComponentSerializer& serializer = _serializer(typeId);

        // Serialize
        DataValueComponentWriter writer;
        serializer._save(component, writer);

        members[typeName] = writer.dataValue();
    }

    dataValue = DataValue(members);
}

void EntitySerializer::save(Entity& entity, WriteStream& stream)
{
    if (!entity)
    {
        throw Error("Entity is null");
    }
    Scene* scene = entity._scene;
    Entity::Id id = entity._id;

    auto& components = scene->_entityComponents[id];
    stream.writeByte((uint8_t)components.size());

    for (auto& pair : components)
    {
        BaseComponent* component = pair.second.get();
        ComponentTypeId typeId = component->componentTypeId();
        const BaseComponentSerializer& serializer = _serializer(typeId);

        stream.writeByte((uint8_t)typeId);

        // Serialize
        BinaryComponentWriter writer(stream);
        serializer._save(component, writer);
    }
}

void EntitySerializer::load(Entity& entity, const DataValue& dataValue, AssetCache& assetCache)
{
    if (!entity)
    {
        throw Error("Entity is null");
    }

    for (const std::string& typeName : dataValue.memberNames())
    {
        ComponentTypeId typeId = _typeId(typeName);
        const BaseComponentSerializer& serializer = _serializer(typeId);

        // Create component
        BaseComponent::Ref component = _constructComponent(typeId);

        // Deserialize
        DataValueComponentReader reader(dataValue[typeName]);
        serializer._load(component.get(), reader, assetCache);

        // Add component
        entity._scene->_addComponentWithoutReturn(entity, component);
    }
}

void EntitySerializer::load(Entity& entity, ReadStream& stream, AssetCache& assetCache)
{
    if (!entity)
    {
        throw Error("Entity is null");
    }

    uint8_t componentCount = stream.readByte();
    for (uint8_t i = 0; i < componentCount; ++i)
    {
        ComponentTypeId typeId = stream.readByte();
        const BaseComponentSerializer& serializer = _serializer(typeId);

        // Create component
        BaseComponent::Ref component = _constructComponent(typeId);

        // Deserialize
        BinaryComponentReader reader(stream);
        serializer._load(component.get(), reader, assetCache);

        // Add component
        entity._scene->_addComponentWithoutReturn(entity, component);
    }
}

ComponentTypeId EntitySerializer::_typeId(const std::string& typeName) const
{
    auto it = _componentTypeIds.find(typeName);
    if (it == _componentTypeIds.end())
    {
        throw Error(format("No serializer registered for component type name '%s'", typeName));
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

BaseComponent::Ref EntitySerializer::_constructComponent(ComponentTypeId typeId) const
{
    auto it = _componentConstructors.find(typeId);
    if (it == _componentConstructors.end())
    {
        throw Error(format("No serializer registered for component type id '%d'", typeId));
    }
    return (*it).second();
}