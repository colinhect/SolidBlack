namespace hect
{

template <typename T, typename S>
void Scene::registerComponent(const std::string& componentTypeName)
{
    _entitySerializer.registerComponent<T, S>(componentTypeName);
}

template <typename T>
bool Scene::_hasComponent(const Entity& entity) const
{
    Entity::Id id = entity._id;
    const EntityData& data = _entityData[id];

    if (data.isNull())
    {
        throw Error("Entity is null");
    }

    return data.hasComponent(Component<T>::typeId());
}

template <typename T>
T& Scene::_addComponent(Entity& entity, const BaseComponent::Ref& component)
{
    _addComponentWithoutReturn(entity, component);
    return *(T*)component.get();
}

template <typename T>
T& Scene::_component(const Entity& entity)
{
    ComponentTypeId typeId = Component<T>::typeId();

    if (!_hasComponent<T>(entity))
    {
        throw Error(format("Entity does not have a component with type id '%d'", typeId));
    }

    // Return the component at the type index
    return *dynamic_cast<T*>(_entityComponents[entity._id][typeId].get());
}

}