#pragma once

namespace hect
{

class AssetCache;

///
/// Base asset entry.
class AssetEntryBase
{
public:

    ///
    /// Virtual destructor.
    virtual ~AssetEntryBase() { }
};

///
/// Refers to the asset at a path.
template <typename T>
class AssetEntry :
    public AssetEntryBase
{
public:

    ///
    /// Constructs an asset entry given the asset cache and the path to the
    /// asset.
    ///
    /// \param assetCache The asset cache.
    /// \param path The path to the asset.
    AssetEntry(AssetCache& assetCache, const Path& path);

    ///
    /// Returns a shared pointer to the asset.
    std::shared_ptr<T> get();

    ///
    /// Returns the path of the asset.
    const Path& path() const;

private:
    void _load();

    AssetCache* _assetCache;
    Path _path;

    std::shared_ptr<T> _asset;

    bool _errorOccurred;
    std::string _errorMessage;
};

}

#include "AssetEntry.inl"