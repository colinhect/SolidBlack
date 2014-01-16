#pragma once

namespace hect
{

///
/// A handle for an asset.
template <typename T>
class AssetHandle
{
public:

    ///
    /// An array of asset handles.
    typedef std::vector<AssetHandle<T>> Array;

    ///
    /// Constructs an empty asset handle.
    AssetHandle();

    ///
    /// Constructs an asset handle given an asset entry.
    ///
    /// \param entry The asset entry.
    AssetHandle(const std::shared_ptr<AssetEntry<T>>& entry);

    ///
    /// Returns a reference to the asset.
    ///
    /// \throws Error If the asset failed to load.
    T& get() const;

    ///
    /// Returns a shared pointer to the asset.
    ///
    /// \throws Error If the asset failed to load.
    std::shared_ptr<T> getShared() const;

    ///
    /// Returns the path to the asset.
    const Path& path() const;

private:
    std::shared_ptr<AssetEntry<T>> _entry;
};

}

#include "AssetHandle.inl"