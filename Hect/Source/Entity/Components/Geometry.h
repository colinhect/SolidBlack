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
    /// Returns the mesh.
    AssetHandle<Mesh>& mesh();

    ///
    /// Returns the mesh.
    const AssetHandle<Mesh>& mesh() const;

    ///
    /// Sets the mesh.
    ///
    /// \param mesh The new mesh.
    void setMesh(const AssetHandle<Mesh>& mesh);

    ///
    /// Returns the material.
    AssetHandle<Material>& material();

    ///
    /// Returns the material.
    const AssetHandle<Material>& material() const;

    ///
    /// Sets the material.
    ///
    /// \param material The new material.
    void setMaterial(const AssetHandle<Material>& material);

private:
    AssetHandle<Mesh> _mesh;
    AssetHandle<Material> _material;
};

class GeometrySerializer :
    public ComponentSerializer<Geometry>
{
public:
    void save(const Geometry& geometry, ComponentWriter& writer) const;
    void load(Geometry& geometry, ComponentReader& reader, AssetCache& assetCache) const;
};

}