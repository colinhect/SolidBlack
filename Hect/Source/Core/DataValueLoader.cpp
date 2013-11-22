#include "Hect.h"

using namespace hect;

void AssetLoader<DataValue>::load(DataValue& dataValue, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.storage().openFileForRead(assetPath);
    dataValue = JsonParser().parse(stream);
}
