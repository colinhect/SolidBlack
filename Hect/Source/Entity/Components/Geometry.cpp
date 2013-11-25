#include "Hect.h"

using namespace hect;

Geometry::Geometry() :
    _transform(nullptr)
{
}

void Geometry::onActivate(Entity& entity)
{
    if (entity.hasComponent<Transform>())
    {
        _transform = &entity.component<Transform>();
    }
}

void Geometry::onDeactivate(Entity& entity)
{
    _transform = nullptr;
}

void Geometry::addMesh(Mesh::Ref mesh, Material::Ref material)
{
    _meshes.push_back(mesh);
    _materials.push_back(material);

    _boundingBox.expandToInclude(mesh->boundingBox());
}

void Geometry::render(const Camera& camera, RenderingSystem& renderingSystem)
{
    if (!_transform)
    {
        return;
    }

    size_t i = 0;
    while (i < _meshes.size())
    {
        Mesh& mesh = *_meshes[i];
        Material& material = *_materials[i];

        if (mesh.indexCount() > 0)
        {
            if (camera.frustum().testAxisAlignedBox(mesh.boundingBox()) != FrustumTestResult::Outside)
            {
                renderingSystem.renderMesh(mesh, material, *_transform);
            }
        }

        ++i;
    }
}

void Geometry::renderDebug(const Camera& camera, DebugRenderingSystem& renderingSystem)
{
    if (!_transform)
    {
        return;
    }

    if (_boundingBox.hasSize())
    {
        Vector3<> scale = _boundingBox.maximum() - _boundingBox.minimum();
        Vector4<> color = Vector4<>(1.0, 0.0, 0.0, 1.0);
        renderingSystem.renderWireframeBox(_transform->position(), scale, color);
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