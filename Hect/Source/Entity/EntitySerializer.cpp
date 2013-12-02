#include "Hect.h"

using namespace hect;

EntitySerializer::EntitySerializer()
{
    registerComponent<Camera, CameraSerializer>("Camera");
    registerComponent<AmbientLight, AmbientLightSerializer>("AmbientLight");
    registerComponent<DirectionalLight, DirectionalLightSerializer>("DirectionalLight");
    registerComponent<Geometry, GeometrySerializer>("Geometry");
    registerComponent<Transform, TransformSerializer>("Transform");
}

void EntitySerializer::deserialize(Entity& entity, AssetCache& assetCache, const Path& assetPath)
{
    if (!entity)
    {
        throw Error("Entity is null");
    }

    const DataValue& dataValue = *assetCache.get<DataValue>(assetPath);
    for (const std::string& componentTypeName : dataValue.memberNames())
    {
        auto it = _componentTypes.find(componentTypeName);
        if (it == _componentTypes.end())
        {
            throw Error(format("No serializer registered for component type '%s'", componentTypeName.c_str()));
        }

        ComponentTypeId type = (*it).second;

        BaseComponent::Ref component = _componentConstructors[type]();
        _componentSerializers[type]->_deserialize(component.get(), dataValue[componentTypeName], assetCache);
        entity.scene()._addComponentWithoutReturn(entity, component);
    }
}
