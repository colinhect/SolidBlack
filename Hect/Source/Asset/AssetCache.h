namespace hect
{

///
/// Provides cached access to assets loaded from persistant storage.
class AssetCache :
    public Uncopyable
{
public:

    ///
    /// Constructs an asset cache given access to persistent storage.
    ///
    /// \param storage The access to persistent storage.
    AssetCache(Storage& storage);

    ///
    /// Returns a shared reference to the asset at the given path.
    ///
    /// \param path The case-sensitive path to the asset.
    ///
    /// \throws Error If the asset at the given path is of a different type or
    /// failed to load.
    template <typename T>
    std::shared_ptr<T> get(const Path& path);

    ///
    /// Returns a handle for the asset at the given path.
    ///
    /// \remarks The asset is not necessarily loaded immediately.  The handle
    /// provides access to the asset itself.
    ///
    /// \param path The case-sensitive path to the asset.
    ///
    /// \throws Error If the asset at the given path is of a different type.
    template <typename T>
    AssetHandle<T> getHandle(const Path& path);

    ///
    /// Returns access to persistent storage.
    Storage& storage();

private:
    Storage& _storage;

    std::map<Path, std::shared_ptr<AssetEntryBase>> _entries;
};

}

#include "AssetCache.inl"