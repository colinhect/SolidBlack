#include "Hect.h"

using namespace hect;

void AssetLoader<ShaderModule>::load(ShaderModule& shaderModule, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.fileSystem().openFileForRead(assetPath);

    ShaderModuleType type;
    std::string extension = assetPath.extension();
    if (extension == "vert")
    {
        type = ShaderModuleType::Vertex;
    }
    else if (extension == "frag")
    {
        type = ShaderModuleType::Pixel;
    }
    else if (extension == "geom")
    {
        type = ShaderModuleType::Geometry;
    }
    else
    {
        throw Error(format("Unknown shader module type '%s'", extension.c_str()));
    }

    std::string source = stream.readAllToString();
    shaderModule = ShaderModule(assetPath.toString(), type, source);
}
