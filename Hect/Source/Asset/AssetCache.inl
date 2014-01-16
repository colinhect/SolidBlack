namespace hect
{

template <typename T>
T& AssetCache::get(const Path& path)
{
    return *getHandle<T>(path).getShared();
}

template <typename T>
AssetHandle<T> AssetCache::getHandle(const Path& path)
{
    std::shared_ptr<AssetEntry<T>> entry;

    auto it = _entries.find(path);
    if (it == _entries.end())
    {
        // First time this asset was requested so create a new entry
        entry.reset(new AssetEntry<T>(*this, path));

        // Add the new entry to the entry map
        _entries[path] = entry;
    }
    else
    {
        // There is already an entry for this asset.
        entry = std::dynamic_pointer_cast<AssetEntry<T>>((*it).second);

        // Throw an error if the asset is not of the same type as the template
        // type
        if (!entry)
        {
            throw Error(format("Asset '%s' is not of the expected type", path.toString().c_str()));
        }
    }

    return AssetHandle<T>(entry);
}

}