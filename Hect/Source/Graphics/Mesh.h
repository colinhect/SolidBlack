#pragma once

namespace hect
{

///
/// How the primitives of a mesh are rendered.
enum class PrimitiveType
{
    Triangles,
    TriangleStrip,
    Lines,
    LineStrip,
    Points
};

///
/// The type of each index in an index sequence.
enum class IndexType
{
    UnsignedByte,
    UnsignedShort,
    UnsignedInt
};

///
/// A mesh of vertices and indices.
class Mesh :
    public RendererObject
{
    friend class MeshWriter;
public:

    ///
    /// Raw vertex data.
    typedef std::vector<uint8_t> VertexData;

    ///
    /// Raw index data.
    typedef std::vector<uint8_t> IndexData;

    ///
    /// A shared reference to a mesh
    typedef std::shared_ptr<Mesh> Ref;

    ///
    /// An array of shared mesh references.
    typedef std::vector<Mesh::Ref> RefArray;

    ///
    /// Constructs a mesh with the default vertex layout, primitive type,
    /// and index type.
    Mesh();

    ///
    /// Constructs a mesh.
    ///
    /// \param name The name of the mesh.
    /// \param vertexLayout The vertex layout.
    /// \param primitiveType The primitive type.
    /// \param indexType The index type.
    Mesh(const std::string& name, const VertexLayout& vertexLayout, PrimitiveType primitiveType, IndexType indexType);

    ///
    /// Constructs a mesh as a copy from another mesh.
    ///
    /// \param mesh The mesh to copy from.
    Mesh(const Mesh& mesh);

    ///
    /// Returns the name.
    const std::string& name() const;

    ///
    /// Sets the raw vertex data.
    ///
    /// \param vertexData The vertex data to set.  Assumed to conform to the
    /// vertex layout.
    ///
    /// \throws Error If the mesh has vertex data.
    void setVertexData(const VertexData& vertexData);

    ///
    /// Returns the raw vertex data.
    const VertexData& vertexData() const;

    ///
    /// Returns the number of vertices.
    size_t vertexCount() const;

    ///
    /// Sets the raw index data.
    ///
    /// \param indexData The index data to set.  Assumed to conform to the
    /// index type.
    ///
    /// \throws Error If the mesh has vertex data.
    void setIndexData(const IndexData& indexData);

    ///
    /// Returns the raw index data.
    const IndexData& indexData() const;

    ///
    /// Returns the number of indices.
    size_t indexCount() const;

    ///
    /// Returns the size of an index in bytes.
    unsigned indexSize() const;

    ///
    /// Returns the vertex layout.
    const VertexLayout& vertexLayout() const;

    ///
    /// Returns the primitive type.
    PrimitiveType primitiveType() const;

    ///
    /// Returns the index type.
    IndexType indexType() const;

    ///
    /// Returns the bounding box.
    AxisAlignedBox<float>& boundingBox();

    ///
    /// Returns the bounding box.
    const AxisAlignedBox<float>& boundingBox() const;

private:
    std::string _name;

    VertexLayout _vertexLayout;
    PrimitiveType _primitiveType;
    IndexType _indexType;

    VertexData _vertexData;
    IndexData _indexData;

    size_t _vertexCount;
    size_t _indexCount;

    AxisAlignedBox<float> _boundingBox;
};

}