#pragma once

namespace hect
{

///
/// Provides cached access to assets loaded from the file system.
class AssetCache :
    public Uncopyable
{
public:

    ///
    /// Constructs an asset cache given a file system.
    ///
    /// \param fileSystem The file system.
    AssetCache(FileSystem& fileSystem);

    ///
    /// Returns a reference to the asset at the given path.
    ///
    /// \param path The case-sensitive path to the asset.
    ///
    /// \throws Error If the asset at the given path is of a different type or
    /// failed to load.
    template <typename T>
    T& get(const Path& path);

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
    /// Clears all cached resources.
    void clear();

    ///
    /// Returns the file system.
    FileSystem& fileSystem();

private:
    FileSystem& _fileSystem;

    std::map<Path, std::shared_ptr<AssetEntryBase>> _entries;
};

}

#include "AssetCache.inl"