#pragma once

namespace hect
{

///
/// Provides functionality for loading textures from data values.
class TextureDataFormat
{
public:

    ///
    /// Loads a texture from a data value.
    ///
    /// \param texture The texture to load to.
    /// \param name The name of the texture.
    /// \param dataValue The root data value.
    /// \param assetCache The asset cache to use to load referenced assets.
    static void load(Texture& texture, const std::string& name, const DataValue& dataValue, AssetCache& assetCache);

private:
    static TextureFilter _parseTextureFilter(const DataValue& dataValue);
};

}