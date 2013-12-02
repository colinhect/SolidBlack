namespace hect
{

template <typename T>
void ComponentSerializer<T>::save(const T& component, WriteStream& stream) const
{
}

template <typename T>
void ComponentSerializer<T>::load(T& component, ReadStream& stream, AssetCache& assetCache) const
{
}

template <typename T>
void ComponentSerializer<T>::load(T& component, const DataValue& dataValue, AssetCache& assetCache) const
{
}

template <typename T>
void ComponentSerializer<T>::_save(const BaseComponent* component, WriteStream& stream) const
{
    return save(*(const T*)component, stream);
}

template <typename T>
void ComponentSerializer<T>::_load(BaseComponent* component, ReadStream& stream, AssetCache& assetCache) const
{
    load(*(T*)component, stream, assetCache);
}

template <typename T>
void ComponentSerializer<T>::_load(BaseComponent* component, const DataValue& dataValue, AssetCache& assetCache) const
{
    load(*(T*)component, dataValue, assetCache);
}

}