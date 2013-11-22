namespace hect
{

template <typename ComponentType, typename SerializerType>
void Scene::registerSerializer(const std::string& componentTypeName)
{
    if (_componentTypes.find(componentTypeName) != _componentTypes.end())
    {
        throw Error(format("Component type '%s' already has a serializer registered", componentTypeName.c_str()));
    }

    _componentTypes[componentTypeName] = ComponentType::type();
    _componentSerializers[ComponentType::type()] = std::shared_ptr<BaseComponentSerializer>(new SerializerType());
    _componentConstructors[ComponentType::type()] = [] { return std::make_shared<ComponentType>(); };
}

template <typename T>
bool Scene::_hasComponent(const Entity& entity) const
{
    assert(!entity.isNull());
    return _attributes[entity._id].hasComponent(Component<T>::type());
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

    ComponentType type = component->componentType();

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
    return *dynamic_cast<T*>(_components[entity._id][Component<T>::type()].get());
}

}