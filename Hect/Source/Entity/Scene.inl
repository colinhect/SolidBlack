namespace hect
{

template <typename T>
Entity Scene::entityWithComponent()
{
    for (Entity::Id id = 1; id < _attributes.size(); ++id)
    {
        Entity entity(*this, id);
        if (entity && entity.hasComponent<T>())
        {
            return entity; // Found an entity with the component
        }
    }

    return Entity(); // Not found
}

template <typename T>
bool Scene::_hasComponent(const Entity& entity) const
{
    assert(!entity.isNull());
    return _attributes[entity._id].hasComponent(Component<T>::typeId());
}

template <typename T>
T& Scene::_addComponent(Entity& entity, const BaseComponent::Ref& component)
{
    EntityAttributes& attributes = _attributes[entity._id];

#ifdef HECT_DEBUG
    if (_hasComponent<T>(entity))
    {
        throw Error("Attempt to add a component an entity already has");
    }

    if ((_isActivated(entity) && !attributes.hasAttribute(EntityAttribute::MarkedForDeactivation)) ||
        attributes.hasAttribute(EntityAttribute::MarkedForActivation))
    {
        throw Error("Attempt to remove a component from an activated entity");
    }
#endif

    ComponentTypeId typeId = component->componentTypeId();

    // Add the existence of a component of this type to the entity's attributes
    attributes.setHasComponent(typeId, true);

    // Add the component to the entity's components
    _components[entity._id][typeId] = component;

    // Return the new component
    return *(T*)component.get();
}

template <typename T>
void Scene::_removeComponent(Entity& entity)
{
    EntityAttributes& attributes = _attributes[entity._id];

#ifdef HECT_DEBUG
    if (!_hasComponent<T>(entity))
    {
        throw Error("Attempt to remove a component an entity does not have");
    }

    if ((_isActivated(entity) && !attributes.hasAttribute(EntityAttribute::MarkedForDeactivation)) ||
        attributes.hasAttribute(EntityAttribute::MarkedForActivation))
    {
        throw Error("Attempt to remove a component from an activated entity");
    }
#endif

    ComponentTypeId typeId = T::typeId();

    // Remove the existence of a component of this type from the entity's attributes
    attributes.setHasComponent(typeId, false);

    // Remove the component from the entity's components
    _components[entity._id].erase(typeId);
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
    return *dynamic_cast<T*>(_components[entity._id][Component<T>::typeId()].get());
}

}