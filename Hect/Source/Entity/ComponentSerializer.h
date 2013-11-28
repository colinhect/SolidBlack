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
    virtual void _serialize(const BaseComponent* component, DataValue& dataValue) const = 0;
    virtual void _deserialize(BaseComponent* component, const DataValue& dataValue, AssetCache& assetCache) const = 0;
};

///
/// Provides functionality for serializing/deserializing entity components.
template <typename T>
class ComponentSerializer :
    public BaseComponentSerializer
{
public:

    ///
    /// Serializes a component to a data value.
    ///
    /// \param component The component.
    /// \param dataValue The data value to serialize to.
    virtual void serialize(const T& component, DataValue& dataValue) const;

    ///
    /// Deserializes a component from a data value.
    ///
    /// \param component The component.
    /// \param dataValue The data value to deserialize from.
    /// \param assetCache The asset cache to load referenced assets from.
    virtual void deserialize(T& component, const DataValue& dataValue, AssetCache& assetCache) const;

private:
    void _serialize(const BaseComponent* component, DataValue& dataValue) const;
    void _deserialize(BaseComponent* component, const DataValue& dataValue, AssetCache& assetCache) const;
};

}

#include "ComponentSerializer.inl"
