#include "Hect.h"

using namespace hect;

void AssetLoader<Texture>::load(Texture& texture, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.storage().openFileForRead(assetPath);
    TextureJsonFormat().load(texture, stream, assetCache);
}
