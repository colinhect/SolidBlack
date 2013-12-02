#include "Hect.h"

using namespace hect;

EntitySerializer::EntitySerializer()
{
    registerComponent<Camera, CameraSerializer>("Camera");
    registerComponent<AmbientLight, AmbientLightSerializer>("AmbientLight");
    registerComponent<DirectionalLight, DirectionalLightSerializer>("DirectionalLight");
    registerComponent<Geometry, GeometrySerializer>("Geometry");
    registerComponent<Transform, TransformSerializer>("Transform");
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
        BaseComponent* component = pair.second.get();
        
        ComponentTypeId typeId = component->_componentTypeId();
        
        auto it = _componentSerializers.find(typeId);
        if (it == _componentSerializers.end())
        {
            throw Error(format("No serializer registered for component type id '%d'", typeId));
        }

        (*it).second->_save(component, stream);
    }
}

void EntitySerializer::load(Entity& entity, AssetCache& assetCache, ReadStream& stream)
{
    if (!entity)
    {
        throw Error("Entity is null");
    }

    uint8_t componentCount = stream.readByte();
    for (uint8_t i = 0; i < componentCount; ++i)
    {
        ComponentTypeId typeId = stream.readByte();

        auto it = _componentSerializers.find(typeId);
        if (it == _componentSerializers.end())
        {
            throw Error(format("No serializer registered for component type id '%d'", typeId));
        }

        BaseComponent::Ref component = _componentConstructors[typeId]();
        (*it).second->_load(component.get(), stream, assetCache);
        entity.scene()._addComponentWithoutReturn(entity, component);
    }
}

void EntitySerializer::load(Entity& entity, AssetCache& assetCache, const DataValue& dataValue)
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

        BaseComponent::Ref component = _componentConstructors[typeId]();
        _componentSerializers[typeId]->_load(component.get(), dataValue[componentTypeName], assetCache);
        entity.scene()._addComponentWithoutReturn(entity, component);
    }
}