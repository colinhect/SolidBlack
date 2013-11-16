#pragma once

namespace hect
{

///
/// An attribute of a vertex (position, normal, etc).
///
/// \remarks A vertex attribute is made up of a semantic, a type, and a
/// cardinality.  The semantic describes how the attribute is used.  The
/// type describes the type of each component in the attribute.  The
/// cardinality is number of components (of the attributes type) the
/// attribute has.
class VertexAttribute
{
    friend class VertexLayout;
public:

    ///
    /// An array of vertex attributes.
    typedef std::vector<VertexAttribute> Array;

    ///
    /// A semantic describing how a vertex attribute is used.
    enum Semantic
    {

        ///
        /// The position of a vertex.
        Position,

        ///
        /// The normal of a vertex.
        Normal,

        ///
        /// The color of a vertex.
        Color,

        ///
        /// The tangent of a vertex.
        Tangent,

        ///
        /// The binormal of a vertex.
        Binormal,

        ///
        /// The first weight of a vertex.
        Weight0,

        ///
        /// The second weight of a vertex.
        Weight1,

        ///
        /// The third weight of a vertex.
        Weight2,

        ///
        /// The fourth weight of a vertex.
        Weight3,

        ///
        /// The texture coordinates of a vertex for the first texture.
        TextureCoords0,

        ///
        /// The texture coordinates of a vertex for the second texture.
        TextureCoords1,

        ///
        /// The texture coordinates of a vertex for the third texture.
        TextureCoords2,

        ///
        /// The texture coordinates of a vertex for the fourth texture.
        TextureCoords3
    };

    ///
    /// A type of a vertex attribute.
    enum Type
    {

        ///
        /// A 16-bit float.
        /// \remarks Also known as "half".
        Half,

        ///
        /// A 32-bit float.
        Float
    };

    ///
    /// Constructs a vertex attribute.
    ///
    /// \param semantic The semantic.
    /// \param type The type.
    /// \param cardinality The cardinality.
    VertexAttribute(Semantic semantic, Type type, unsigned cardinality);

    ///
    /// Returns the semantic.
    Semantic semantic() const;

    ///
    /// Returns the type of the vertex attribute.
    Type type() const;

    ///
    /// Returns the cardinality.
    unsigned cardinality() const;

    ///
    /// Returns the total size in bytes.
    unsigned size() const;

    ///
    /// Returns the offset into the vertex data in bytes.
    unsigned offset() const;

private:
    Semantic _semantic;
    Type _type;
    unsigned _cardinality;
    unsigned _offset;
};

}