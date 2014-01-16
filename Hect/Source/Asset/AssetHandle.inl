namespace hect
{

template <typename T>
AssetHandle<T>::AssetHandle() :
    _entry(nullptr)
{
}

template <typename T>
AssetHandle<T>::AssetHandle(const std::shared_ptr<AssetEntry<T>>& entry) :
    _entry(entry)
{
}

template <typename T>
T& AssetHandle<T>::get() const
{
    return *getShared();
}

template <typename T>
std::shared_ptr<T> AssetHandle<T>::getShared() const
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

}