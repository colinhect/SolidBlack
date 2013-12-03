#pragma once

namespace hect
{

///
/// A handle for an asset.
template <typename T>
class AssetHandle
{
    friend class AssetCache;
public:

    ///
    /// Constructs an empty asset handle.
    AssetHandle();

    ///
    /// Returns a raw pointer to the asset.
    ///
    /// \warning The lifetime of this pointer is undefined.
    ///
    /// \throws Error If the asset failed to load.
    T* get();

    ///
    /// Returns a shared pointer to the asset.
    ///
    /// \throws Error If the asset failed to load.
    std::shared_ptr<T> getShared();

    ///
    /// Returns the path to the asset.
    const Path& path() const;

private:
    AssetHandle(AssetEntry<T>* entry);

    AssetEntry<T>* _entry;
};

}

#include "AssetHandle.inl"