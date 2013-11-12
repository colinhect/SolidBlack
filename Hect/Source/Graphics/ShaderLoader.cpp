#include "Hect.h"

using namespace hect;

void AssetLoader<Shader>::load(Shader& shader, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.storage().openFileForRead(assetPath);
    ShaderJsonFormat().load(shader, stream, assetCache);
}
