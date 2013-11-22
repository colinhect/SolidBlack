#pragma once

namespace hect
{

class Scene;

class EntityFactory :
    public Uncopyable
{
public:
    EntityFactory(Scene& scene, AssetCache& assetCache);

    Entity createEntity(const Path& path);

    template <typename ComponentType, typename SerializerType>
    void registerSerializer(const std::string& componentTypeName);

private:
    Scene* _scene;
    AssetCache* _assetCache;

    std::map<std::string, EntityComponentType> _componentTypes;
    std::map<EntityComponentType, std::shared_ptr<BaseComponentSerializer>> _componentSerializers;
    std::map<EntityComponentType, std::function<std::shared_ptr<BaseComponent>()>> _componentConstructors;
};

}

#include "EntityFactory.inl"
