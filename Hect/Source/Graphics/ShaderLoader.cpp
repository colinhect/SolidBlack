#include "Hect.h"

using namespace hect;

void AssetLoader<Shader>::load(Shader& shader, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.storage().openFileForRead(assetPath);
    DataValue dataValue = JsonParser().parse(stream);
    ShaderJsonFormat().load(shader, dataValue, assetCache);
}
