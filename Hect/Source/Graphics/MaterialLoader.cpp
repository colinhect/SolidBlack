#include "Hect.h"

using namespace hect;

void AssetLoader<Material>::load(Material& material, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.storage().openFileForRead(assetPath);
    MaterialJsonFormat().load(material, stream, assetCache);
}
