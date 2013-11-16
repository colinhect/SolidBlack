#pragma once

namespace hect
{

class AssetCache;

///
/// Provides the functionality for loading an asset of a certain type.
///
/// \remarks Each asset type implements the load() method for their type.  This
/// is how asset types are hooked into the asset cache.
template <typename T>
class AssetLoader
{
public:

    ///
    /// Loads the asset at the given path.
    ///
    /// \remarks May support multiple file formats.  The format of the asset is
    /// automatically detected.
    ///
    /// \param asset The asset to load to.
    /// \param assetPath The path to the asset.
    /// \param assetCache The asset cache to load referenced assets using.
    static void load(T& asset, const Path& assetPath, AssetCache& assetCache);
};

}