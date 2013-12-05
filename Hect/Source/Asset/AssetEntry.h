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
    friend class AssetCache;
public:

    ///
    /// Returns a shared pointer to the asset.
    std::shared_ptr<T> get();

    ///
    /// Returns the path of the asset.
    const Path& path() const;

private:
    AssetEntry(AssetCache& assetCache, const Path& path);

    void _load();

    AssetCache* _assetCache;
    Path _path;

    std::shared_ptr<T> _asset;

    bool _errorOccurred;
    std::string _errorMessage;
};

}

#include "AssetEntry.inl"