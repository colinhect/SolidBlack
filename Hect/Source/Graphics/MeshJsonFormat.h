#pragma once

namespace hect
{

///
/// Provides functionality for loading meshes from JSON.
class MeshJsonFormat :
    public JsonFormat
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
    VertexAttribute::Semantic _parseAttributeSemantic(const DataValue& dataValue);
    VertexAttribute::Type _parseAttributeType(const DataValue& dataValue);

    std::map<std::string, IndexType> _indexTypes;
    std::map<std::string, PrimitiveType> _primitiveTypes;
    std::map<std::string, VertexAttribute::Semantic> _attributeSemantics;
    std::map<std::string, VertexAttribute::Type> _attributeTypes;
};

}