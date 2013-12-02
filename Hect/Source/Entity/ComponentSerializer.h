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
    virtual void _save(const BaseComponent* component, WriteStream& stream) const = 0;
    virtual void _load(BaseComponent* component, ReadStream& stream, AssetCache& assetCache) const = 0;
    virtual void _load(BaseComponent* component, const DataValue& dataValue, AssetCache& assetCache) const = 0;
};

///
/// Provides functionality for serializing/deserializing entity components.
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
    virtual void save(const T& component, WriteStream& stream) const;

    ///
    /// Deserializes a component from a binary stream
    ///
    /// \param component The component.
    /// \param stream The stream to deserialize from.
    /// \param assetCache The asset cache to load referenced assets from.
    virtual void load(T& component, ReadStream& stream, AssetCache& assetCache) const;

    ///
    /// Deserializes a component from a data value.
    ///
    /// \param component The component.
    /// \param dataValue The data value to deserialize from.
    /// \param assetCache The asset cache to load referenced assets from.
    virtual void load(T& component, const DataValue& dataValue, AssetCache& assetCache) const;

private:
    void _save(const BaseComponent* component, WriteStream& stream) const;
    void _load(BaseComponent* component, ReadStream& stream, AssetCache& assetCache) const;
    void _load(BaseComponent* component, const DataValue& dataValue, AssetCache& assetCache) const;
};

}

#include "ComponentSerializer.inl"
