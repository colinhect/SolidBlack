namespace hect
{

template <typename T>
void System::requireComponent()
{
    _requiredAttributes.setHasComponent(T::type(), true);
}

}