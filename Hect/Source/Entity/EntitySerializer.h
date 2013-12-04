#pragma once

namespace hect
{

class Scene;

class EntitySerializer :
    public Uncopyable
{
public:
    EntitySerializer();

    void save(Entity& entity, DataValue& dataValue);
    void save(Entity& entity, WriteStream& stream);
    void load(Entity& entity, const DataValue& dataValue, AssetCache& assetCache);
    void load(Entity& entity, ReadStream& stream, AssetCache& assetCache);

    template <typename T, typename S>
    void registerComponent(const std::string& componentTypeName);

private:
    
    ComponentTypeId _typeId(const std::string& typeName) const;
    const std::string& _typeName(ComponentTypeId typeId) const;
    const BaseComponentSerializer& _serializer(ComponentTypeId typeId) const;
    BaseComponent::Ref _constructComponent(ComponentTypeId typeId) const;

    // Component types mapped to component type names
    std::map<ComponentTypeId, std::string> _componentTypeNames;

    // Component type names mapped to component types
    std::map<std::string, ComponentTypeId> _componentTypeIds;

    // Component types mapped to registered component serializers
    std::map<ComponentTypeId, BaseComponentSerializer::Ref> _componentSerializers;

    // Component types mapped to component constructors
    std::map<ComponentTypeId, std::function<BaseComponent::Ref()>> _componentConstructors;
};

}

#include "EntitySerializer.inl"