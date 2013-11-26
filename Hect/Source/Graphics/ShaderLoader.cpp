#include "Hect.h"

using namespace hect;

void AssetLoader<Shader>::load(Shader& shader, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.fileSystem().openFileForRead(assetPath);
    DataValue dataValue = JsonParser().parse(stream);
    ShaderJsonFormat().load(shader, dataValue, assetCache);
}
