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
const Path& AssetHandle<T>::path() const
{
    if (!_entry)
    {
        throw Error("Asset entry is null");
    }
    return _entry->path();
}

template <typename T>
AssetHandle<T>::AssetHandle(AssetEntry<T>* entry) :
    _entry(entry)
{
}

}