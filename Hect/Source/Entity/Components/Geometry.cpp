#include "Hect.h"

using namespace hect;

void Geometry::addMesh(Mesh::Ref mesh, Material::Ref material)
{
    _meshes.push_back(mesh);
    _materials.push_back(material);
}

void Geometry::render(const Camera& camera, RenderingSystem& renderingSystem)
{
    if (!hasEntity() || !entity().hasComponent<Transform>())
    {
        return;
    }

    Transform& transform = entity().component<Transform>();

    size_t i = 0;
    while (i < _meshes.size())
    {
        Mesh& mesh = *_meshes[i];
        Material& material = *_materials[i];

        if (mesh.indexCount() > 0)
        {
            renderingSystem.renderMesh(mesh, material, transform);
        }

        ++i;
    }
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