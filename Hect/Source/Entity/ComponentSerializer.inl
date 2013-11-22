namespace hect
{

template <typename T>
void ComponentSerializer<T>::serialize(const T& component, DataValue& dataValue) const
{
}

template <typename T>
void ComponentSerializer<T>::deserialize(T& component, const DataValue& dataValue, AssetCache& assetCache) const
{
}

template <typename T>
void ComponentSerializer<T>::_serialize(const BaseComponent* component, DataValue& dataValue) const
{
    return serialize(*(const T*)component, dataValue);
}

template <typename T>
void ComponentSerializer<T>::_deserialize(BaseComponent* component, const DataValue& dataValue, AssetCache& assetCache) const
{
    deserialize(*(T*)component, dataValue, assetCache);
}

}