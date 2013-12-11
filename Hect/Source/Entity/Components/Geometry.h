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
    /// Adds a surface.
    ///
    /// \param mesh The mesh.
    /// \param material The material.
    void addSurface(const AssetHandle<Mesh>& mesh, const AssetHandle<Material>& material);

    ///
    /// Returns the number of surfaces.
    size_t surfaceCount() const;

    ///
    /// Returns the meshes.
    AssetHandle<Mesh>::Array& meshes();

    ///
    /// Returns the meshes.
    const AssetHandle<Mesh>::Array& meshes() const;
    
    ///
    /// Returns the materials
    AssetHandle<Material>::Array& materials();

    ///
    /// Returns the materials
    const AssetHandle<Material>::Array& materials() const;

private:
    AssetHandle<Mesh>::Array _meshes;
    AssetHandle<Material>::Array _materials;
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