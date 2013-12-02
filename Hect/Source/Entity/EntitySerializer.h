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
    /// Serializes an entity to a binary stream.
    ///
    /// \param entity The entity to serialize.
    /// \param stream The stream to write to.
    void save(Entity& entity, WriteStream& stream);

    ///
    /// Deserializes an entity from a binary stream.
    ///
    /// \param entity The entity to deserialize to.
    /// \param stream The stream to read from.
    void load(Entity& entity, AssetCache& assetCache, ReadStream& stream);

    ///
    /// Deserializes an entity from a data value.
    ///
    /// \param entity The entity to deserialize to.
    /// \param assetCache The asset cache to load referenced assets from.
    /// \param dataValue The data value to deserialize from.
    void load(Entity& entity, AssetCache& assetCache, const DataValue& dataValue);

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