namespace hect
{

///
/// A mesh of vertices and indices.
class Mesh :
    public GpuObject
{
    friend class MeshBuilder;
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
    /// How the primitives of the mesh are rendered.
    enum PrimitiveType
    {
        Triangles,
        TriangleStrip,
        Lines,
        LineStrip,
        Points
    };

    ///
    /// The type of each index in an index sequence.
    enum IndexType
    {
        Unsigned8,
        Unsigned16,
        Unsigned32
    };

    ///
    /// Constructs a mesh with the default vertex layout, primitive type,
    /// and index type.
    Mesh();

    ///
    /// Constructs a mesh.
    ///
    /// \param vertexLayout The vertex layout.
    /// \param primitiveType The primitive type.
    /// \param indexType The index type.
    Mesh(const VertexLayout& vertexLayout, PrimitiveType primitiveType, IndexType indexType);

    ///
    /// Constructs a mesh as a copy from another mesh.
    ///
    /// \param mesh The mesh to copy from.
    Mesh(const Mesh& mesh);

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
    /// Sets the vertex layout.
    ///
    /// \param vertexLayout The new vertex layout.
    ///
    /// \throws Error If the mesh has vertex data.
    void setVertexLayout(const VertexLayout& vertexLayout);

    ///
    /// Returns the primitive type.
    PrimitiveType primitiveType() const;

    ///
    /// Sets the primitive type.
    ///
    /// \param primitiveType The new primitive type.
    void setPrimitiveType(PrimitiveType primitiveType);

    ///
    /// Returns the index type.
    IndexType indexType() const;

    ///
    /// Sets the index type.
    ///
    /// \param indexType The new index type.
    ///
    /// \throws Error If the mesh has index data.
    void setIndexType(IndexType indexType);

    ///
    /// Returns the bounding box.
    AxisAlignedBox<float>& boundingBox();

    ///
    /// Returns the bounding box.
    const AxisAlignedBox<float>& boundingBox() const;

private:
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