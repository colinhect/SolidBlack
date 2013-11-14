#include "Hect.h"

using namespace hect;

TextureJsonFormat::TextureJsonFormat()
{
    _textureFilters["Nearest"] = Texture::Nearest;
    _textureFilters["Linear"] = Texture::Linear;
}

void TextureJsonFormat::load(Texture& texture, const DataValue& dataValue, AssetCache& assetCache)
{
    // Image
    if (dataValue["image"].isString())
    {
        AssetHandle<Image> handle = assetCache.getHandle<Image>(dataValue["image"].asString());
        texture = Texture(handle.getShared());
    }

    // Min filter
    if (dataValue["minFilter"].isString())
    {
        texture.setMinFilter(_parseTextureFilter(dataValue["minFilter"]));
    }

    // Mag filter
    if (dataValue["magFilter"].isString())
    {
        texture.setMagFilter(_parseTextureFilter(dataValue["magFilter"]));
    }

    // Wrapped
    if (dataValue["wrapped"].isBool())
    {
        texture.setWrapped(dataValue["wrapped"].asBool());
    }

    // Mipmapped
    if (dataValue["mipmapped"].isBool())
    {
        texture.setMipmapped(dataValue["mipmapped"].asBool());
    }
}

Texture::Filter TextureJsonFormat::_parseTextureFilter(const DataValue& dataValue)
{
    auto it = _textureFilters.find(dataValue.asString());
    if (it == _textureFilters.end())
    {
        throw Error(format("Invalid texture filter '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}