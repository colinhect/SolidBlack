#include "Hect.h"

using namespace hect;

void Geometry::addMesh(Mesh::Ref mesh, Material::Ref material)
{
    _meshes.push_back(mesh);
    _materials.push_back(material);
}

Mesh::RefArray& Geometry::meshes()
{
    return _meshes;
}

Material::RefArray& Geometry::materials()
{
    return _materials;
}

void GeometrySerializer::deserialize(Geometry& geometry, const DataValue& dataValue, AssetCache& assetCache) const
{
    for (const DataValue& meshValue : dataValue["meshes"])
    {
        if (meshValue.isArray())
        {
            Mesh::Ref mesh = assetCache.get<Mesh>(meshValue[0].asString());
            Material::Ref material = assetCache.get<Material>(meshValue[1].asString());
            geometry.addMesh(mesh, material);
        }
    }
}