namespace hect
{

template <typename T>
bool Scene::_hasComponent(const Entity& entity) const
{
#ifdef HECT_DEBUG
    if (entity.isNull())
    {
        throw Error("Entity is null");
    }
#endif

    return _entityData[entity._id].hasComponent(Component<T>::typeId());
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

#ifdef HECT_DEBUG
    if (!_hasComponent<T>(entity))
    {
        throw Error(format("Entity does not have a component with type id '%d'", typeId));
    }
#endif

    // Return the component at the type index
    return *dynamic_cast<T*>(_entityComponents[entity._id][typeId].get());
}

}