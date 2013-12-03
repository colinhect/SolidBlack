#include "Hect.h"

using namespace hect;

void AssetLoader<Mesh>::load(Mesh& mesh, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.fileSystem().openFileForRead(assetPath);
    DataValue dataValue;
    DataValueJsonFormat::load(dataValue, stream);
    MeshDataFormat::load(mesh, dataValue);
}
