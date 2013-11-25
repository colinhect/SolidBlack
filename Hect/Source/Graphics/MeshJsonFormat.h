#pragma once

namespace hect
{

///
/// Provides functionality for loading meshes from JSON.
class MeshJsonFormat
{
public:

    ///
    /// Constucts a JSON format for meshes.
    MeshJsonFormat();

    ///
    /// Loads a mesh from a stream of JSON data.
    ///
    /// \param mesh The mesh to load to.
    /// \param dataValue The root data value of the JSON data.
    void load(Mesh& mesh, const DataValue& dataValue);

private:
    IndexType _parseIndexType(const DataValue& dataValue);
    PrimitiveType _parsePrimitiveType(const DataValue& dataValue);
    VertexAttributeSemantic _parseAttributeSemantic(const DataValue& dataValue);
    VertexAttributeType _parseAttributeType(const DataValue& dataValue);

    std::map<std::string, IndexType> _indexTypes;
    std::map<std::string, PrimitiveType> _primitiveTypes;
    std::map<std::string, VertexAttributeSemantic> _attributeSemantics;
    std::map<std::string, VertexAttributeType> _attributeTypes;
};

}