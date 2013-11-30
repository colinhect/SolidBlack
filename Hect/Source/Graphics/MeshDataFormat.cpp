#include "Hect.h"

using namespace hect;

void MeshDataFormat::load(Mesh& mesh, const DataValue& dataValue)
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

IndexType MeshDataFormat::_parseIndexType(const DataValue& dataValue)
{
    static std::map<std::string, IndexType> indexTypes;

    if (indexTypes.empty())
    {
        indexTypes["UnsignedByte"] = IndexType::UnsignedByte;
        indexTypes["UnsignedShort"] = IndexType::UnsignedShort;
        indexTypes["UnsignedInt"] = IndexType::UnsignedInt;
    }

    auto it = indexTypes.find(dataValue.asString());
    if (it == indexTypes.end())
    {
        throw Error(format("Invalid index type '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

PrimitiveType MeshDataFormat::_parsePrimitiveType(const DataValue& dataValue)
{
    static std::map<std::string, PrimitiveType> primitiveTypes;

    if (primitiveTypes.empty())
    {
        primitiveTypes["Triangles"] = PrimitiveType::Triangles;
        primitiveTypes["TriangleStrip"] = PrimitiveType::TriangleStrip;
        primitiveTypes["Lines"] = PrimitiveType::Lines;
        primitiveTypes["LineStrip"] = PrimitiveType::LineStrip;
        primitiveTypes["Points"] = PrimitiveType::Points;
    }

    auto it = primitiveTypes.find(dataValue.asString());
    if (it == primitiveTypes.end())
    {
        throw Error(format("Invalid primitive type '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

VertexAttributeSemantic MeshDataFormat::_parseAttributeSemantic(const DataValue& dataValue)
{
    static std::map<std::string, VertexAttributeSemantic> attributeSemantics;

    if (attributeSemantics.empty())
    {
        attributeSemantics["Position"] = VertexAttributeSemantic::Position;
        attributeSemantics["Normal"] = VertexAttributeSemantic::Normal;
        attributeSemantics["Color"] = VertexAttributeSemantic::Color;
        attributeSemantics["Tangent"] = VertexAttributeSemantic::Tangent;
        attributeSemantics["Binormal"] = VertexAttributeSemantic::Binormal;
        attributeSemantics["Weight0"] = VertexAttributeSemantic::Weight0;
        attributeSemantics["Weight1"] = VertexAttributeSemantic::Weight1;
        attributeSemantics["Weight2"] = VertexAttributeSemantic::Weight2;
        attributeSemantics["Weight3"] = VertexAttributeSemantic::Weight3;
        attributeSemantics["TextureCoords0"] = VertexAttributeSemantic::TextureCoords0;
        attributeSemantics["TextureCoords1"] = VertexAttributeSemantic::TextureCoords1;
        attributeSemantics["TextureCoords2"] = VertexAttributeSemantic::TextureCoords2;
        attributeSemantics["TextureCoords3"] = VertexAttributeSemantic::TextureCoords3;
    }

    auto it = attributeSemantics.find(dataValue.asString());
    if (it == attributeSemantics.end())
    {
        throw Error(format("Invalid vertex attribute semantic '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

VertexAttributeType MeshDataFormat::_parseAttributeType(const DataValue& dataValue)
{
    static std::map<std::string, VertexAttributeType> attributeTypes;

    if (attributeTypes.empty())
    {
        attributeTypes["Half"] = VertexAttributeType::Half;
        attributeTypes["Float"] = VertexAttributeType::Float;
    }

    auto it = attributeTypes.find(dataValue.asString());
    if (it == attributeTypes.end())
    {
        throw Error(format("Invalid vertex attribute type '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}