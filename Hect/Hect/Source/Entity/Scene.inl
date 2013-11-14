namespace hect
{

template <typename T>
bool Scene::_hasComponent(const Entity& entity) const
{
    assert(!entity.isNull());
    return _attributes[entity._id].hasComponent(EntityComponent<T>::type());
}

template <typename T>
T& Scene::_addComponent(const Entity& entity, const std::shared_ptr<BaseComponent>& component)
{
#ifdef HECT_DEBUG
    if (_hasComponent<T>(entity))
    {
        throw Error("Attempt to add a component an entity already has");
    }

    if (_isActivated(entity))
    {
        throw Error("Attempt to add a component to an activated entity");
    }
#endif

    EntityComponentType type = component->componentType();

    // Add the existence of a component of this type to the entity's attributes
    _attributes[entity._id].setHasComponent(type, true);

    // Add the component to the entity's components
    _components[entity._id][type] = component;

    // Return the new component
    return *(T*)component.get();
}

template <typename T>
T& Scene::_component(const Entity& entity)
{
#ifdef HECT_DEBUG
    if (!_hasComponent<T>(entity))
    {
        throw Error("Attempt to get a component an entity does not have");
    }
#endif

    // Return the component at the type index
    return *dynamic_cast<T*>(_components[entity._id][EntityComponent<T>::type()].get());
}

}