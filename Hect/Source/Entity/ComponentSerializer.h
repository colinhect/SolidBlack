#pragma once

namespace hect
{

///
/// Base component serializer.
class BaseComponentSerializer
{
public:

    ///
    /// A shared reference to a base component serializer.
    typedef std::shared_ptr<BaseComponentSerializer> Ref;

    virtual ~BaseComponentSerializer() { }

    ///
    /// Serializes a component using a data writer.
    ///
    /// \param component The component.
    /// \param writer The data writer.
    virtual void save(const BaseComponent* component, DataWriter& writer) const = 0;

    ///
    /// Deserializes a component using a data reader.
    ///
    /// \param component The component.
    /// \param reader The data reader.
    /// \param assetCache The asset cache to load referenced assets from.
    virtual void load(BaseComponent* component, DataReader& reader, AssetCache& assetCache) const = 0;
};

///
/// Provides functionality for serializing/deserializing an entity component.
template <typename T>
class ComponentSerializer :
    public BaseComponentSerializer
{
public:

    ///
    /// Serializes a component using a data writer.
    ///
    /// \param component The component.
    /// \param writer The data writer.
    virtual void save(const T& component, DataWriter& writer) const;

    ///
    /// Deserializes a component using a data reader.
    ///
    /// \param component The component.
    /// \param reader The data reader.
    /// \param assetCache The asset cache to load referenced assets from.
    virtual void load(T& component, DataReader& reader, AssetCache& assetCache) const;

    void save(const BaseComponent* component, DataWriter& writer) const;
    void load(BaseComponent* component, DataReader& reader, AssetCache& assetCache) const;
};

}

#include "ComponentSerializer.inl"
