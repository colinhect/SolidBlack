#include "Hect.h"

using namespace hect;

void EntitySerializer::deserialize(Entity& entity, AssetCache& assetCache, const Path& assetPath)
{
    if (!entity)
    {
        throw Error("Attempt to deserialize to a null entity");
    }

    if (entity.isActivated())
    {
        entity.deactivate();
    }

    const DataValue& dataValue = *assetCache.get<DataValue>(assetPath);
    for (const std::string& componentTypeName : dataValue.memberNames())
    {
        if (_componentTypes.find(componentTypeName) == _componentTypes.end())
        {
            throw Error(format("No serializer registered for component type '%s'", componentTypeName.c_str()));
        }

        ComponentTypeId type = _componentTypes[componentTypeName];

        BaseComponent::Ref component = _componentConstructors[type]();
        _componentSerializers[type]->_deserialize(component.get(), dataValue[componentTypeName], assetCache);
        entity.addComponent(component);
    }
    
    entity.activate();
}
