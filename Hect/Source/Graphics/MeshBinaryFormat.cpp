#include "Hect.h"

using namespace hect;

const uint32_t MeshBinaryFormat::Signature = 0xFE01;

void MeshBinaryFormat::load(Mesh& mesh, const std::string& name, ReadStream& stream)
{
    // Check the signature
    uint32_t signature = stream.readUnsignedInt();
    if (signature != Signature)
    {
        throw Error("The stream does not contain valid mesh data");
    }

    // Read attribute count
    uint8_t attributeCount = stream.readUnsignedByte();

    // Read each attribute
    VertexAttribute::Array attributes;
    for (uint8_t i = 0; i < attributeCount; ++i)
    {
        VertexAttributeSemantic semantic = (VertexAttributeSemantic)stream.readUnsignedByte();
        VertexAttributeType type = (VertexAttributeType)stream.readUnsignedByte();
        unsigned cardinality = (unsigned)stream.readUnsignedByte();

        attributes.push_back(VertexAttribute(semantic, type, cardinality));
    }
    
    // Create vertex layout
    VertexLayout vertexLayout(attributes);

    // Read the primitive/index type
    PrimitiveType primitiveType = (PrimitiveType)stream.readUnsignedByte();
    IndexType indexType = (IndexType)stream.readUnsignedByte();

    // Create the mesh
    mesh = Mesh(name, vertexLayout, primitiveType, indexType);
    
    // Read vertex data
    uint32_t vertexDataSize = stream.readUnsignedInt();
    Mesh::VertexData vertexData(vertexDataSize);
    stream.readBytes(&vertexData[0], vertexDataSize);
    
    // Read index data
    uint32_t indexDataSize = stream.readUnsignedInt();
    Mesh::IndexData indexData(indexDataSize);
    stream.readBytes(&indexData[0], indexDataSize);
    
    // Set vertex/index data
    mesh.setVertexData(vertexData);
    mesh.setIndexData(indexData);
}

void MeshBinaryFormat::save(const Mesh& mesh, WriteStream& stream)
{
    // Write the signature
    stream.writeUnsignedInt(Signature);

    // Write the attribute count
    const VertexLayout& vertexLayout = mesh.vertexLayout();
    size_t attributeCount = vertexLayout.attributes().size();
    stream.writeUnsignedByte((uint8_t)attributeCount);
    
    // Write each attribute
    for (const VertexAttribute& attribute : vertexLayout.attributes())
    {
        stream.writeUnsignedByte((uint8_t)attribute.semantic());
        stream.writeUnsignedByte((uint8_t)attribute.type());
        stream.writeUnsignedByte((uint8_t)attribute.cardinality());
    }

    // Write the primitive/index type
    stream.writeUnsignedByte((uint8_t)mesh.primitiveType());
    stream.writeUnsignedByte((uint8_t)mesh.indexType());
    
    // Write vertex data
    uint32_t vertexDataSize = (uint32_t)(mesh.vertexCount() * vertexLayout.vertexSize());
    stream.writeUnsignedInt(vertexDataSize);
    stream.writeBytes(&mesh.vertexData()[0], vertexDataSize);

    // Write index data
    uint32_t indexDataSize = (uint32_t)(mesh.indexCount() * mesh.indexSize());
    stream.writeUnsignedInt(indexDataSize);
    stream.writeBytes(&mesh.indexData()[0], indexDataSize);
}