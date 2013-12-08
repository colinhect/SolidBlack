#include "Hect.h"

using namespace hect;

void AssetLoader<Material>::load(Material& material, const Path& assetPath, AssetCache& assetCache)
{
    DataValue dataValue;
    {
        FileReadStream stream = assetCache.fileSystem().openFileForRead(assetPath);
        DataValueJsonFormat::load(dataValue, stream);
    }
    MaterialDataFormat::load(material, assetPath.toString(), dataValue, assetCache);
}
