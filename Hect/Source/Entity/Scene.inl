namespace hect
{

template <typename T, typename S>
void Scene::registerComponent(const std::string& componentTypeName)
{
    if (_componentTypes.find(componentTypeName) != _componentTypes.end())
    {
        throw Error(format("Component type '%s' is already registered", componentTypeName.c_str()));
    }

    _componentTypes[componentTypeName] = T::typeId();
    _componentSerializers[T::typeId()] = std::shared_ptr<BaseComponentSerializer>(new S());
    _componentConstructors[T::typeId()] = [] { return std::make_shared<T>(); };
}

template <typename T>
bool Scene::_hasComponent(const Entity& entity) const
{
    assert(!entity.isNull());
    return _attributes[entity._id].hasComponent(Component<T>::typeId());
}

template <typename T>
T& Scene::_addComponent(Entity& entity, const std::shared_ptr<BaseComponent>& component)
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