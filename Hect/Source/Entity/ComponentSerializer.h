#pragma once

namespace hect
{

class BaseComponentSerializer
{
    friend class EntitySerializer;
public:
    typedef std::shared_ptr<BaseComponentSerializer> Ref;

    virtual ~BaseComponentSerializer() { }

protected:
    virtual void _save(const BaseComponent* component, ComponentWriter& writer) const = 0;
    virtual void _load(BaseComponent* component, ComponentReader& reader, AssetCache& assetCache) const = 0;
};

///
/// Provides functionality for serializing/deserializing an entity component.
template <typename T>
class ComponentSerializer :
    public BaseComponentSerializer
{
public:

    ///
    /// Serializes a component to a binary stream.
    ///
    /// \param component The component.
    /// \param stream The stream to serialize to.
    virtual void save(const T& component, ComponentWriter& writer) const;

    ///
    /// Deserializes a component from a binary stream
    ///
    /// \param component The component.
    /// \param stream The stream to deserialize from.
    /// \param assetCache The asset cache to load referenced assets from.
    virtual void load(T& component, ComponentReader& reader, AssetCache& assetCache) const;

private:
    void _save(const BaseComponent* component, ComponentWriter& writer) const;
    void _load(BaseComponent* component, ComponentReader& reader, AssetCache& assetCache) const;
};

}

#include "ComponentSerializer.inl"
