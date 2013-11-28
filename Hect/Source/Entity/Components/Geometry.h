#pragma once

namespace hect
{

///
/// A geometry component.
class Geometry :
    public Renderable
{
public:

    ///
    /// Adds a mesh to the geometry with a material.
    ///
    /// \param mesh The mesh to add.
    /// \param material The material to render the mesh with.
    void addMesh(Mesh::Ref mesh, Material::Ref material);

    ///
    /// \copydoc Renderable::render()
    void render(const Camera& camera, RenderingSystem& renderingSystem);

private:
    Mesh::RefArray _meshes;
    Material::RefArray _materials;
};

class GeometrySerializer :
    public ComponentSerializer<Geometry>
{
public:
    void deserialize(Geometry& geometry, const DataValue& dataValue, AssetCache& assetCache) const;
};

}