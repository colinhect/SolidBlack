#include "Hect.h"

using namespace hect;

MeshJsonFormat::MeshJsonFormat()
{
    _indexTypes["UnsignedByte"] = IndexType::UnsignedByte;
    _indexTypes["UnsignedShort"] = IndexType::UnsignedShort;
    _indexTypes["UnsignedInt"] = IndexType::UnsignedInt;

    _primitiveTypes["Triangles"] = PrimitiveType::Triangles;
    _primitiveTypes["TriangleStrip"] = PrimitiveType::TriangleStrip;
    _primitiveTypes["Lines"] = PrimitiveType::Lines;
    _primitiveTypes["LineStrip"] = PrimitiveType::LineStrip;
    _primitiveTypes["Points"] = PrimitiveType::Points;

    _attributeSemantics["Position"] = VertexAttributeSemantic::Position;
    _attributeSemantics["Normal"] = VertexAttributeSemantic::Normal;
    _attributeSemantics["Color"] = VertexAttributeSemantic::Color;
    _attributeSemantics["Tangent"] = VertexAttributeSemantic::Tangent;
    _attributeSemantics["Binormal"] = VertexAttributeSemantic::Binormal;
    _attributeSemantics["Weight0"] = VertexAttributeSemantic::Weight0;
    _attributeSemantics["Weight1"] = VertexAttributeSemantic::Weight1;
    _attributeSemantics["Weight2"] = VertexAttributeSemantic::Weight2;
    _attributeSemantics["Weight3"] = VertexAttributeSemantic::Weight3;
    _attributeSemantics["TextureCoords0"] = VertexAttributeSemantic::TextureCoords0;
    _attributeSemantics["TextureCoords1"] = VertexAttributeSemantic::TextureCoords1;
    _attributeSemantics["TextureCoords2"] = VertexAttributeSemantic::TextureCoords2;
    _attributeSemantics["TextureCoords3"] = VertexAttributeSemantic::TextureCoords3;

    _attributeTypes["Half"] = VertexAttributeType::Half;
    _attributeTypes["Float"] = VertexAttributeType::Float;
}

void MeshJsonFormat::load(Mesh& mesh, const DataValue& dataValue)
{
    // Index type (optional)
    if (dataValue["indexType"].isString())
    {
        IndexType indexType = _parseIndexType(dataValue["indexType"].asString());
        mesh.setIndexType(indexType);
    }

    // Primitive type (optional)
    if (dataValue["primitiveType"].isString())
    {
        PrimitiveType primitiveType = _parsePrimitiveType(dataValue["primitiveType"].asString());
        mesh.setPrimitiveType(primitiveType);
    }

    // Vertex layout (optional)
    if (dataValue["vertexLayout"].isArray())
    {
        VertexAttribute::Array attributes;
        for (const DataValue& attribute : dataValue["vertexLayout"])
        {
            auto semantic =_parseAttributeSemantic(attribute["semantic"].asString());
            auto type = _parseAttributeType(attribute["type"].asString());
            auto cardinality = attribute["cardinality"].asUnsigned();

            attributes.push_back(VertexAttribute(semantic, type, cardinality));
        }
        mesh.setVertexLayout(VertexLayout(attributes));
    }

    MeshBuilder meshBuilder(mesh);

    // Add the vertices
    for (const DataValue& vertex : dataValue["vertices"])
    {
        meshBuilder.addVertex();

        // For each attribute
        for (const DataValue& attribute : vertex)
        {
            auto semantic = _parseAttributeSemantic(attribute["semantic"].asString());

            switch (semantic)
            {
            case VertexAttributeSemantic::Position:
            case VertexAttributeSemantic::Normal:
            case VertexAttributeSemantic::Tangent:
            case VertexAttributeSemantic::Binormal:
                meshBuilder.setAttributeData(semantic, attribute["data"].asVector3());
                break;
            default:
                meshBuilder.setAttributeData(semantic, attribute["data"].asVector2());
            }
        }
    }

    // Add the indices
    for (const DataValue& index : dataValue["indices"])
    {
        unsigned indexValue = index.asUnsigned();
        meshBuilder.addIndex(indexValue);
    }
}

IndexType MeshJsonFormat::_parseIndexType(const DataValue& dataValue)
{
    auto it = _indexTypes.find(dataValue.asString());
    if (it == _indexTypes.end())
    {
        throw Error(format("Invalid index type '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

PrimitiveType MeshJsonFormat::_parsePrimitiveType(const DataValue& dataValue)
{
    auto it = _primitiveTypes.find(dataValue.asString());
    if (it == _primitiveTypes.end())
    {
        throw Error(format("Invalid primitive type '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

VertexAttributeSemantic MeshJsonFormat::_parseAttributeSemantic(const DataValue& dataValue)
{
    auto it = _attributeSemantics.find(dataValue.asString());
    if (it == _attributeSemantics.end())
    {
        throw Error(format("Invalid vertex attribute semantic '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

VertexAttributeType MeshJsonFormat::_parseAttributeType(const DataValue& dataValue)
{
    auto it = _attributeTypes.find(dataValue.asString());
    if (it == _attributeTypes.end())
    {
        throw Error(format("Invalid vertex attribute type '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}