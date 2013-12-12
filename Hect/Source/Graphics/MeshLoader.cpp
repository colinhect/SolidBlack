#include "Hect.h"

using namespace hect;

void AssetLoader<Mesh>::load(Mesh& mesh, const Path& assetPath, AssetCache& assetCache)
{
    FileReadStream stream = assetCache.fileSystem().openFileForRead(assetPath);

    uint32_t signature = stream.readUnsignedInt();
    stream.seek(0);

    if (signature == MeshBinaryFormat::Signature)
    {
        MeshBinaryFormat::load(mesh, assetPath.toString(), stream);
    }
    else
    {
        DataValue dataValue;
        DataValueJsonFormat::load(dataValue, stream);
        MeshDataValueFormat::load(mesh, assetPath.toString(), dataValue);
    }
}
