#include "Hect.h"

using namespace hect;

EntityFactory::EntityFactory(Scene& scene, AssetCache& assetCache) :
    _scene(&scene),
    _assetCache(&assetCache)
{
    registerSerializer<Camera, CameraSerializer>("Camera");
    registerSerializer<Geometry, GeometrySerializer>("Geometry");
    registerSerializer<Transform, TransformSerializer>("Transform");
}

Entity EntityFactory::createEntity(const Path& path)
{
    Entity entity = _scene->createEntity();

    const DataValue& dataValue = *_assetCache->get<DataValue>(path);
    for (const std::string& componentTypeName : dataValue.memberNames())
    {
        if (_componentTypes.find(componentTypeName) == _componentTypes.end())
        {
            throw Error(format("No serializer registered for component type '%s'", componentTypeName.c_str()));
        }

        EntityComponentType type = _componentTypes[componentTypeName];

        std::shared_ptr<BaseComponent> component = _componentConstructors[type]();
        _componentSerializers[type]->_fromDataValue(component.get(), dataValue[componentTypeName], *_assetCache);
        _scene->_addComponentFromFactory(entity, component);
    }

    entity.activate();
    return entity;
}