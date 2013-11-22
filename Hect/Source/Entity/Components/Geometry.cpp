#include "Hect.h"

using namespace hect;

Geometry::Geometry() :
    _transform(nullptr)
{
}

void Geometry::onActivate(Entity& entity)
{
    _transform = nullptr;
    if (entity.hasComponent<Transform>())
    {
        _transform = &entity.component<Transform>();
    }
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

void GeometrySerializer::fromDataValue(Geometry& geometry, const DataValue& dataValue, AssetCache& assetCache) const
{
    Mesh::Ref mesh;
    Material::Ref material;

    const DataValue& meshValue = dataValue["mesh"];
    if (meshValue.isString())
    {
        mesh = assetCache.get<Mesh>(meshValue.asString());
    }

    const DataValue& materialValue = dataValue["material"];
    if (materialValue.isString())
    {
        material = assetCache.get<Material>(materialValue.asString());
    }

    geometry.addMesh(mesh, material);
}

DataValue GeometrySerializer::toDataValue(const Geometry& geometry) const
{
    DataValue::Object members;
    return DataValue(members);
}