#pragma once

namespace hect
{

class Scene;

///
/// Provides functionality for serializing/deserializing entities.
class EntitySerializer :
    public Uncopyable
{
public:

    ///
    /// Constructs an entity serializer with all of the default components
    /// registered.
    EntitySerializer();

    ///
    /// Deserializes an entity from an asset.
    ///
    /// \param entity The entity to deserialize to (cannot be null).
    /// \param assetCache The asset cache to get the assets from.
    /// \param assetPath The path to the asset describing the entity.
    void deserialize(Entity& entity, AssetCache& assetCache, const Path& assetPath);

    ///
    /// Registers a component with its serializer.
    ///
    /// \param componentTypeName The type name of the component.
    ///
    /// \throws Error If the component type is already registered.
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