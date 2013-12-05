#pragma once

namespace hect
{

class Scene;

///
/// Provides functionality for registering component serializers to a component
/// type and for serializing/deserializing entities.
class EntitySerializer
{
public:

    ///
    /// Constructs an entity serializer with all built-in components registered
    /// with their serializers.
    EntitySerializer();

    ///
    /// Serializes an entity's components to a data value.
    ///
    /// \param entity The entity.
    /// \param dataValue The data value.
    ///
    /// \throws Error If the entity is null.
    void save(Entity& entity, DataValue& dataValue);

    ///
    /// Serializes an entity's components to a binary stream.
    ///
    /// \param entity The entity.
    /// \param stream The stream to write to.
    ///
    /// \throws Error If the entity is null.
    void save(Entity& entity, WriteStream& stream);

    ///
    /// Deserializes and adds components to an entity from a data value.
    ///
    /// \param entity The entity.
    /// \param dataValue The data value.
    /// \param assetCache The asset cache to use to load referenced assets.
    ///
    /// \throws Error If the entity is null or activated.
    void load(Entity& entity, const DataValue& dataValue, AssetCache& assetCache);

    ///
    /// Deserializes and adds components to an entity from a binary stream.
    ///
    /// \param entity The entity.
    /// \param stream The stream to read from.
    /// \param assetCache The asset cache to use to load referenced assets.
    ///
    /// \throws Error If the entity is null or activated.
    void load(Entity& entity, ReadStream& stream, AssetCache& assetCache);

    ///
    /// Registers a component with its serializer.
    ///
    /// \param componentTypeName The type name of the component.
    ///
    /// \throws Error If the component type is already registered.
    template <typename T, typename S>
    void registerComponent(const std::string& componentTypeName);

private:
    ComponentTypeId _typeId(const std::string& typeName) const;
    const std::string& _typeName(ComponentTypeId typeId) const;
    const BaseComponentSerializer& _serializer(ComponentTypeId typeId) const;
    BaseComponent* _constructComponent(ComponentTypeId typeId) const;

    // Component types mapped to component type names
    std::map<ComponentTypeId, std::string> _componentTypeNames;

    // Component type names mapped to component types
    std::map<std::string, ComponentTypeId> _componentTypeIds;

    // Component types mapped to registered component serializers
    std::map<ComponentTypeId, BaseComponentSerializer::Ref> _componentSerializers;

    // Component types mapped to component constructors
    std::map<ComponentTypeId, std::function<BaseComponent*()>> _componentConstructors;
};

}

#include "EntitySerializer.inl"