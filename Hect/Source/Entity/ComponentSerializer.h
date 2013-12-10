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

    ///
    /// Virtual destructor.
    virtual ~BaseComponentSerializer() { }

    ///
    /// Serializes a component using a component writer.
    ///
    /// \param component The component.
    /// \param writer The component writer.
    virtual void save(const BaseComponent* component, DataWriter& writer) const = 0;

    ///
    /// Deserializes a component using a component reader.
    ///
    /// \param component The component.
    /// \param reader The component reader.
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
    /// \copydoc BaseComponentSerializer::save()
    virtual void save(const T& component, DataWriter& writer) const;

    ///
    /// \copydoc BaseComponentSerializer::load()
    virtual void load(T& component, DataReader& reader, AssetCache& assetCache) const;

    ///
    /// \copydoc BaseComponentSerializer::save()
    void save(const BaseComponent* component, DataWriter& writer) const;

    ///
    /// \copydoc BaseComponentSerializer::load()
    void load(BaseComponent* component, DataReader& reader, AssetCache& assetCache) const;
};

}

#include "ComponentSerializer.inl"
