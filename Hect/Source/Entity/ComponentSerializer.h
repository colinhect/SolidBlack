#pragma once

namespace hect
{

/// \cond INTERNAL

class BaseComponentSerializer
{
    friend class Scene;
public:
    virtual ~BaseComponentSerializer() { }

protected:
    virtual void _fromDataValue(BaseComponent* component, const DataValue& dataValue, AssetCache& assetCache) const = 0;
    virtual DataValue _toDataValue(const BaseComponent* component) const = 0;
};

/// \endcond
    
template <typename T>
class ComponentSerializer :
    public BaseComponentSerializer
{
public:
    virtual void fromDataValue(T& component, const DataValue& dataValue, AssetCache& assetCache) const { }
    virtual DataValue toDataValue(const T& component) const { return DataValue(); }

private:
    void _fromDataValue(BaseComponent* component, const DataValue& dataValue, AssetCache& assetCache) const
    {
        fromDataValue(*(T*)component, dataValue, assetCache);
    }

    DataValue _toDataValue(const BaseComponent* component) const
    {
        return toDataValue(*(const T*)component);
    }
};

}

#include "ComponentSerializer.h"
