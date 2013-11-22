#pragma once

namespace hect
{

///
/// A geoemtry component.
class Geometry :
    public Renderable
{
public:

    ///
    /// Constructs a geometry component.
    Geometry();

    ///
    /// \copydoc BaseComponent::onActivate()
    void onActivate(Entity& entity);

    ///
    /// Adds a mesh to the geometry with a material.
    ///
    /// \param mesh The mesh to add.
    /// \param material The material to render the mesh with.
    void addMesh(Mesh::Ref mesh, Material::Ref material);

    ///
    /// \copydoc Renderable::render()
    void render(const Camera& camera, RenderingSystem& renderingSystem);

    ///
    /// \copydoc Renderable::renderDebug()
    void renderDebug(const Camera& camera, DebugRenderingSystem& renderingSystem);

private:
    Mesh::RefArray _meshes;
    Material::RefArray _materials;
    Transform* _transform;
    AxisAlignedBox<> _boundingBox;
};


class GeometrySerializer :
    public ComponentSerializer<Geometry>
{
public:
    void deserialize(Geometry& geometry, const DataValue& dataValue, AssetCache& assetCache) const;
};

}