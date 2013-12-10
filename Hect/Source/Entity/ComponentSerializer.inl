namespace hect
{

template <typename T>
void ComponentSerializer<T>::save(const T& component, DataWriter& writer) const
{
    component;
    writer;
}

template <typename T>
void ComponentSerializer<T>::load(T& component, DataReader& reader, AssetCache& assetCache) const
{
    component;
    reader;
    assetCache;
}

template <typename T>
void ComponentSerializer<T>::save(const BaseComponent* component, DataWriter& writer) const
{
    // Cast the component into its type
    const T& typedComponent = *(const T*)component;

    // And call the typed version of save
    return save(typedComponent, writer);
}

template <typename T>
void ComponentSerializer<T>::load(BaseComponent* component, DataReader& reader, AssetCache& assetCache) const
{
    // Cast the component into its type
    T& typedComponent = *(T*)component;

    // And call the typed version of load
    load(typedComponent, reader, assetCache);
}

}