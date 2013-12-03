namespace hect
{

template <typename T>
void ComponentSerializer<T>::save(const T& component, ComponentWriter& writer) const
{
}

template <typename T>
void ComponentSerializer<T>::load(T& component, ComponentReader& reader, AssetCache& assetCache) const
{
}

template <typename T>
void ComponentSerializer<T>::_save(const BaseComponent* component, ComponentWriter& writer) const
{
    return save(*(const T*)component, writer);
}

template <typename T>
void ComponentSerializer<T>::_load(BaseComponent* component, ComponentReader& reader, AssetCache& assetCache) const
{
    load(*(T*)component, reader, assetCache);
}

}