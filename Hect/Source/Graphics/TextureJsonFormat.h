#pragma once

namespace hect
{

///
/// Provides functionality for loading textures from JSON.
class TextureJsonFormat
{
public:

    ///
    /// Constucts a JSON format for textures.
    TextureJsonFormat();

    ///
    /// Loads a texture from a stream of JSON data.
    ///
    /// \param texture The texture to load to.
    /// \param dataValue The root data value of the JSON data.
    /// \param assetCache The asset cache to use to load referenced assets.
    void load(Texture& texture, const DataValue& dataValue, AssetCache& assetCache);

private:
    Texture::Filter _parseTextureFilter(const DataValue& dataValue);

    std::map<std::string, Texture::Filter> _textureFilters;
};

}