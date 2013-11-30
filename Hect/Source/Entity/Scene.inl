namespace hect
{

template <typename T>
Entity Scene::entityWithComponent()
{
    size_t foundEntities = 0;
    Entity::Id id = 0;
    while (foundEntities < _entityCount)
    {
        Entity entity(*this, id);
        if (entity)
        {
            ++foundEntities;
            if (entity.hasComponent<T>())
            {
                return entity; // Found an entity with the component
            }
        }

        ++id;
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
    _addComponentWithoutReturn(entity, component);
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
    return *dynamic_cast<T*>(_components[entity._id][Component<T>::typeId()].get());
}

}