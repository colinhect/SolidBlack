#include "Hect.h"

using namespace hect;

void AssetLoader<DataValue>::load(DataValue& dataValue, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.fileSystem().openFileForRead(assetPath);
    std::string json = stream.readAllToString();
    DataValueJsonFormat::load(dataValue, json);
}
