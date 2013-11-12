#include "Hect.h"

using namespace hect;

void AssetLoader<Mesh>::load(Mesh& mesh, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.storage().openFileForRead(assetPath);
    MeshJsonFormat().load(mesh, stream);
}
