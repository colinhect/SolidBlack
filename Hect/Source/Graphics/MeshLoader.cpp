#include "Hect.h"

using namespace hect;

void AssetLoader<Mesh>::load(Mesh& mesh, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.storage().openFileForRead(assetPath);
    DataValue dataValue = JsonParser().parse(stream);
    MeshJsonFormat().load(mesh, dataValue);
}
