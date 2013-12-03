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

    DataValue::Object members;

    auto& components = entity.scene()._entityComponents[entity.id()];
    for (auto& pair : components)
    {
        ComponentTypeId typeId = pair.first;
        std::string typeName = _componentTypeNames[typeId];
        BaseComponent* component = pair.second.get();

        auto it = _componentSerializers.find(typeId);
        if (it == _componentSerializers.end())
        {
            throw Error(format("No serializer registered for component type id '%d'", typeId));
        }

        BaseComponentSerializer* serializer = (*it).second.get();

        // Serialize
        DataValueComponentWriter writer;
        serializer->_save(component, writer);

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

    auto& components = entity.scene()._entityComponents[entity.id()];
    stream.writeByte((uint8_t)components.size());

    for (auto& pair : components)
    {
        ComponentTypeId typeId = pair.first;
        stream.writeByte((uint8_t)typeId);

        std::string typeName = _componentTypeNames[typeId];
        BaseComponent* component = pair.second.get();

        auto it = _componentSerializers.find(typeId);
        if (it == _componentSerializers.end())
        {
            throw Error(format("No serializer registered for component type id '%d'", typeId));
        }

        BaseComponentSerializer* serializer = (*it).second.get();

        // Serialize
        BinaryComponentWriter writer(stream);
        serializer->_save(component, writer);
    }
}

void EntitySerializer::load(Entity& entity, const DataValue& dataValue, AssetCache& assetCache)
{
    if (!entity)
    {
        throw Error("Entity is null");
    }

    for (const std::string& componentTypeName : dataValue.memberNames())
    {
        auto it = _componentTypes.find(componentTypeName);
        if (it == _componentTypes.end())
        {
            throw Error(format("No serializer registered for component type '%s'", componentTypeName.c_str()));
        }

        ComponentTypeId typeId = (*it).second;
        BaseComponentSerializer* serializer = _componentSerializers[typeId].get();

        // Create component
        BaseComponent::Ref component = _componentConstructors[typeId]();

        // Deserialize
        DataValueComponentReader reader(dataValue[componentTypeName]);
        serializer->_load(component.get(), reader, assetCache);

        // Add component
        entity.scene()._addComponentWithoutReturn(entity, component);
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

        auto it = _componentTypeNames.find(typeId);
        if (it == _componentTypeNames.end())
        {
            throw Error(format("No serializer registered for component type id '%d'", typeId));
        }

        BaseComponentSerializer* serializer = _componentSerializers[typeId].get();

        // Create component
        BaseComponent::Ref component = _componentConstructors[typeId]();

        // Deserialize
        BinaryComponentReader reader(stream);
        serializer->_load(component.get(), reader, assetCache);

        // Add component
        entity.scene()._addComponentWithoutReturn(entity, component);
    }
}