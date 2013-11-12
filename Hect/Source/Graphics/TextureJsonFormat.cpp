#include "Hect.h"

using namespace hect;

TextureJsonFormat::TextureJsonFormat()
{
    _textureFilters["Nearest"] = Texture::Nearest;
    _textureFilters["Linear"] = Texture::Linear;
}

void TextureJsonFormat::load(Texture& texture, ReadStream& stream, AssetCache& assetCache)
{
    DataValue root = JsonParser().parse(stream);

    // Image
    if (root["image"].isString())
    {
        AssetHandle<Image> handle = assetCache.getHandle<Image>(root["image"].asString());
        texture = Texture(handle.getShared());
    }

    // Min filter
    if (root["minFilter"].isString())
    {
        texture.setMinFilter(_parseTextureFilter(root["minFilter"]));
    }

    // Mag filter
    if (root["magFilter"].isString())
    {
        texture.setMagFilter(_parseTextureFilter(root["magFilter"]));
    }

    // Wrapped
    if (root["wrapped"].isBool())
    {
        texture.setWrapped(root["wrapped"].asBool());
    }

    // Mipmapped
    if (root["mipmapped"].isBool())
    {
        texture.setMipmapped(root["mipmapped"].asBool());
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