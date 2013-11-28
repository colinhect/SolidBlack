#pragma once

namespace hect
{

class AssetCache;

class AssetEntryBase
{
public:
    virtual ~AssetEntryBase() { }
};

template <typename T>
class AssetEntry :
    public AssetEntryBase
{
    friend class AssetCache;
public:
    std::shared_ptr<T> get();

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