namespace hect
{

template <typename T>
void EntitySystem::requireComponent()
{
    _requiredAttributes.setHasComponent(T::type(), true);
}

}