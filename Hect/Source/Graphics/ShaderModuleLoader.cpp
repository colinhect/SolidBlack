#include "Hect.h"

using namespace hect;

void AssetLoader<ShaderModule>::load(ShaderModule& shaderModule, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.storage().openFileForRead(assetPath);

    ShaderModule::Type type;
    std::string extension = assetPath.extension();
    if (extension == "vert")
    {
        type = ShaderModule::Vertex;
    }
    else if (extension == "frag")
    {
        type = ShaderModule::Pixel;
    }
    else if (extension == "geom")
    {
        type = ShaderModule::Geometry;
    }
    else
    {
        throw Error(format("Unknown shader module type '%s'", extension.c_str()));
    }

    std::string source = stream.readAllToString();
    shaderModule = ShaderModule(type, source);
}
