#include "Hect.h"

using namespace hect;

Geometry::Geometry(Transform& transform) :
    _transform(&transform)
{
}

void Geometry::addMesh(Mesh::Ref mesh, Material::Ref material)
{
    _meshes.push_back(mesh);
    _materials.push_back(material);

    _boundingBox.expandToInclude(mesh->boundingBox());
}

void Geometry::render(const Camera& camera, RenderingSystem& renderingSystem)
{
    size_t i = 0;
    while (i < _meshes.size())
    {
        Mesh& mesh = *_meshes[i];
        Material& material = *_materials[i];

        if (mesh.vertexCount() > 0 && mesh.indexCount() > 0)
        {
            if (camera.frustum().testAxisAlignedBox(mesh.boundingBox()))
            {
                renderingSystem.renderMesh(mesh, material, *_transform);
            }
        }

        ++i;
    }
}

void Geometry::renderDebug(const Camera& camera, DebugRenderingSystem& renderingSystem)
{
    if (_boundingBox.hasSize())
    {
        Vector3<> scale = _boundingBox.maximum() - _boundingBox.minimum();
        Vector4<> color = Vector4<>(1.0, 0.0, 0.0, 1.0);
        renderingSystem.renderWireframeBox(_transform->position(), scale, color);
    }
}
