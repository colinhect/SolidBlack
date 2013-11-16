#pragma once

namespace hect
{

///
/// An ordered layout of vertex attributes.
class VertexLayout
{
public:

    ///
    /// Creates the default vertex layout.
    static VertexLayout createDefault();

    ///
    /// Constructs an empty vertex layout.
    VertexLayout();

    ///
    /// Constructs a vertex layout given vertex attributes.
    ///
    /// \param attributes The attributes in the layout (in order).
    VertexLayout(const VertexAttribute::Array& attributes);

    ///
    /// Returns the attribute with the given semantic (null if no attribute
    /// exists with the semantic).
    ///
    /// \param semantic The semantic to find the attribute for.
    const VertexAttribute* attributeWithSemantic(VertexAttribute::Semantic semantic) const;

    /// Returns the attributes.
    const VertexAttribute::Array& attributes() const;

    ///
    /// Returns the total size in bytes of a vertex in this layout.
    unsigned vertexSize() const;

private:
    VertexAttribute::Array _attributes;
    unsigned _vertexSize;
};

}