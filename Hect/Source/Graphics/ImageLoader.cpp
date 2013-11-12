#include "Hect.h"

using namespace hect;

void AssetLoader<Image>::load(Image& image, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.storage().openFileForRead(assetPath);
    ImagePngFormat().load(image, stream);
}
