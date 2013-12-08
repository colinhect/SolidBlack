#include "Hect.h"

using namespace hect;

void TextureDataValueFormat::load(Texture& texture, const std::string& name, const DataValue& dataValue, AssetCache& assetCache)
{
    // Image
    if (dataValue["image"].isString())
    {
        AssetHandle<Image> handle = assetCache.getHandle<Image>(dataValue["image"].asString());
        texture = Texture(name, handle.getShared());
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

TextureFilter TextureDataValueFormat::_parseTextureFilter(const DataValue& dataValue)
{
    static std::map<std::string, TextureFilter> textureFilters;

    if (textureFilters.empty())
    {
        textureFilters["Nearest"] = TextureFilter::Nearest;
        textureFilters["Linear"] = TextureFilter::Linear;
    }

    auto it = textureFilters.find(dataValue.asString());
    if (it == textureFilters.end())
    {
        throw Error(format("Invalid texture filter '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}