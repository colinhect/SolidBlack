#pragma once

namespace hect
{

///
/// A geometry component.
class Geometry :
    public Component<Geometry>
{
public:

    ///
    /// Adds a mesh to the geometry with a material.
    ///
    /// \param mesh The mesh to add.
    /// \param material The material to render the mesh with.
    void addMesh(Mesh::Ref mesh, Material::Ref material);

    ///
    /// Returns the meshes.
    Mesh::RefArray& meshes();

    ///
    /// Returns the materials.
    Material::RefArray& materials();

private:
    Mesh::RefArray _meshes;
    Material::RefArray _materials;
};

class GeometrySerializer :
    public ComponentSerializer<Geometry>
{
public:
    void save(const Geometry& geometry, WriteStream& stream) const;
    void load(Geometry& geometry, ReadStream& stream, AssetCache& assetCache) const;

    void load(Geometry& geometry, const DataValue& dataValue, AssetCache& assetCache) const;
};

}