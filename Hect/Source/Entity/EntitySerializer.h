#pragma once

namespace hect
{

class Scene;

class EntitySerializer :
    public Uncopyable
{
public:
    EntitySerializer();

    void load(Entity& entity, const DataValue& dataValue, AssetCache& assetCache);

    template <typename T, typename S>
    void registerComponent(const std::string& componentTypeName);

private:

    // Component type names mapped to component types
    std::map<std::string, ComponentTypeId> _componentTypes;

    // Component types mapped to registered component serializers
    std::map<ComponentTypeId, BaseComponentSerializer::Ref> _componentSerializers;

    // Component types mapped to component constructors
    std::map<ComponentTypeId, std::function<BaseComponent::Ref()>> _componentConstructors;
};

}

#include "EntitySerializer.inl"