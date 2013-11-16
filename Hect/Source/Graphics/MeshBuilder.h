#pragma once

namespace hect
{

///
/// Provides an interface for building a mesh without knowledge of the
/// vertex layout.
class MeshBuilder
{
public:

    ///
    /// Constructs a mesh builder given a mesh to build on.
    ///
    /// \param mesh The mesh to build on.
    MeshBuilder(Mesh& mesh);

    ///
    /// Adds a new vertex.
    ///
    /// \returns The index of the added vertex.
    size_t addVertex();

    ///
    /// Sets attribute data of the most recently added vertex for a given
    /// semantic.
    ///
    /// \param semantic The semantic of the attribute to set the data for.
    /// \param value The value.
    void setAttributeData(VertexAttribute::Semantic semantic, float value);

    ///
    /// Sets attribute data of the most recently added vertex for a given
    /// semantic.
    ///
    /// \param semantic The semantic of the attribute to set the data for.
    /// \param value The value.
    void setAttributeData(VertexAttribute::Semantic semantic, const Vector2<float>& value);

    ///
    /// Sets attribute data of the most recently added vertex for a given
    /// semantic.
    ///
    /// \param semantic The semantic of the attribute to set the data for.
    /// \param value The value.
    void setAttributeData(VertexAttribute::Semantic semantic, const Vector3<float>& value);

    ///
    /// Sets attribute data of the most recently added vertex for a given
    /// semantic.
    ///
    /// \param semantic The semantic of the attribute to set the data for.
    /// \param value The value.
    void setAttributeData(VertexAttribute::Semantic semantic, const Vector4<float>& value);

    ///
    /// Adds an index.
    void addIndex(uint64_t value);

private:
    void _setComponentValue(const VertexAttribute* attribute, unsigned index, float value);

    template <typename T>
    void _setAttributeData(const VertexAttribute& attribute, const T& value);

    Mesh* _mesh;
    size_t _vertexDataIndex;
};

}

#include "MeshBuilder.inl"