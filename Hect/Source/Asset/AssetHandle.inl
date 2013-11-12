namespace hect
{

template <typename T>
AssetHandle<T>::AssetHandle() :
    _entry(nullptr)
{
}

template <typename T>
T* AssetHandle<T>::get()
{
    return getShared().get();
}

template <typename T>
std::shared_ptr<T> AssetHandle<T>::getShared()
{
    if (_entry)
    {
        return _entry->get();
    }
    return std::shared_ptr<T>();
}

template <typename T>
AssetHandle<T>::AssetHandle(AssetEntry<T>* entry) :
    _entry(entry)
{
}

}