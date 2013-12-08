#pragma once

namespace hect
{

///
/// Provides functionality for loading meshes from data values.
class MeshDataFormat
{
public:

    ///
    /// Loads a mesh from a data value.
    ///
    /// \param name The name of the mesh.
    /// \param mesh The mesh to load to.
    /// \param dataValue The root data value.
    static void load(Mesh& mesh, const std::string& name, const DataValue& dataValue);

private:
    static IndexType _parseIndexType(const DataValue& dataValue);
    static PrimitiveType _parsePrimitiveType(const DataValue& dataValue);
    static VertexAttributeSemantic _parseAttributeSemantic(const DataValue& dataValue);
    static VertexAttributeType _parseAttributeType(const DataValue& dataValue);

};

}