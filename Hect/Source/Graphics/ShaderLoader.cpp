#include "Hect.h"

using namespace hect;

void AssetLoader<Shader>::load(Shader& shader, const Path& assetPath, AssetCache& assetCache)
{
    DataValue dataValue;
    {
        FileReadStream stream = assetCache.fileSystem().openFileForRead(assetPath);
        DataValueJsonFormat::load(dataValue, stream);
    }
    ShaderDataFormat::load(shader, assetPath.toString(), dataValue, assetCache);
}
