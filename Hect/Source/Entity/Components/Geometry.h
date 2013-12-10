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

///
/// Serializer for Geometry.
class GeometrySerializer :
    public ComponentSerializer<Geometry>
{
public:

    ///
    /// See BaseComponentSerializer::save()
    void save(const Geometry& geometry, DataWriter& writer) const;

    ///
    /// See BaseComponentSerializer::load()
    void load(Geometry& geometry, DataReader& reader, AssetCache& assetCache) const;
};

}