#include "Hect.h"

using namespace hect;

void AssetLoader<Texture>::load(Texture& texture, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.fileSystem().openFileForRead(assetPath);
    DataValue dataValue = JsonParser().parse(stream);
    TextureJsonFormat().load(texture, dataValue, assetCache);
}
