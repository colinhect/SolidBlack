#include "Hect.h"

using namespace hect;

AssetHandle<Mesh>& Geometry::mesh()
{
    return _mesh;
}

const AssetHandle<Mesh>& Geometry::mesh() const
{
    return _mesh;
}

void Geometry::setMesh(const AssetHandle<Mesh>& mesh)
{
    _mesh = mesh;
}

AssetHandle<Material>& Geometry::material()
{
    return _material;
}

const AssetHandle<Material>& Geometry::material() const
{
    return _material;
}

void Geometry::setMaterial(const AssetHandle<Material>& material)
{
    _material = material;
}

void GeometrySerializer::save(const Geometry& geometry, ComponentWriter& writer) const
{
    writer.writeString("mesh", geometry.mesh().path().toString());
    writer.writeString("material", geometry.material().path().toString());
}

void GeometrySerializer::load(Geometry& geometry, ComponentReader& reader, AssetCache& assetCache) const
{
    if (!reader.hasValue("mesh") || !reader.hasValue("material"))
    {
        return;
    }

    std::string meshPath = reader.readString("mesh");
    std::string materialPath = reader.readString("material");

    AssetHandle<Mesh> mesh = assetCache.getHandle<Mesh>(meshPath);
    AssetHandle<Material> material = assetCache.getHandle<Material>(materialPath);

    geometry.setMesh(mesh);
    geometry.setMaterial(material);
}