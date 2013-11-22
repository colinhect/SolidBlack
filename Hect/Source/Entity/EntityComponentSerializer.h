#pragma once

namespace hect
{

class BaseComponentSerializer
{
    friend class EntityFactory;
public:
    virtual ~BaseComponentSerializer() { }

protected:
    virtual void _fromDataValue(BaseComponent* component, const DataValue& dataValue, AssetCache& assetCache) const = 0;
    virtual DataValue _toDataValue(const BaseComponent* component) const = 0;
};
    
template <typename T>
class EntityComponentSerializer :
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

#include "EntityComponentSerializer.h"