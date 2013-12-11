#include "Hect.h"

using namespace hect;

void Geometry::addSurface(const AssetHandle<Mesh>& mesh, const AssetHandle<Material>& material)
{
    _meshes.push_back(mesh);
    _materials.push_back(material);
}

size_t Geometry::surfaceCount() const
{
    return _meshes.size();
}

AssetHandle<Mesh>::Array& Geometry::meshes()
{
    return _meshes;
}

const AssetHandle<Mesh>::Array& Geometry::meshes() const
{
    return _meshes;
}

AssetHandle<Material>::Array& Geometry::materials()
{
    return _materials;
}

const AssetHandle<Material>::Array& Geometry::materials() const
{
    return _materials;
}

void GeometrySerializer::save(const Geometry& geometry, DataWriter& writer) const
{
    size_t surfaceCount = geometry.surfaceCount();

    writer.beginArray("surfaces");
    for (size_t i = 0; i < surfaceCount; ++i)
    {
        writer.beginObject();
        writer.writeString("mesh", geometry.meshes()[i].path().toString());
        writer.writeString("material", geometry.materials()[i].path().toString());
        writer.endObject();
    }
    writer.endArray();
}

void GeometrySerializer::load(Geometry& geometry, DataReader& reader, AssetCache& assetCache) const
{
    if (reader.beginArray("surfaces"))
    {
        while (!reader.endArray())
        {
            if (reader.beginObject())
            {
                if (reader.hasMember("mesh") && reader.hasMember("material"))
                {
                    std::string meshPath = reader.readString("mesh");
                    std::string materialPath = reader.readString("material");

                    AssetHandle<Mesh> mesh = assetCache.getHandle<Mesh>(meshPath);
                    AssetHandle<Material> material = assetCache.getHandle<Material>(materialPath);

                    geometry.addSurface(mesh, material);
                }

            }
            reader.endObject();
        }
    }
}