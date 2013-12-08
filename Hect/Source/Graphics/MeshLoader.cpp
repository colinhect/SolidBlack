#include "Hect.h"

using namespace hect;

void AssetLoader<Mesh>::load(Mesh& mesh, const Path& assetPath, AssetCache& assetCache)
{
    DataValue dataValue;
    {
        FileReadStream stream = assetCache.fileSystem().openFileForRead(assetPath);
        DataValueJsonFormat::load(dataValue, stream);
    }
    MeshDataFormat::load(mesh, assetPath.toString(), dataValue);
}
