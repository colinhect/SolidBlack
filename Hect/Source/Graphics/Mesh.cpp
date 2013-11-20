#include "Hect.h"

using namespace hect;

Mesh::Mesh() :
    _vertexLayout(VertexLayout::createDefault()),
    _primitiveType(PrimitiveType::Triangles),
    _indexType(IndexType::UnsignedShort),
    _vertexCount(0),
    _indexCount(0)
{
}

Mesh::Mesh(const VertexLayout& vertexLayout, PrimitiveType primitiveType, IndexType indexType) :
    _vertexLayout(vertexLayout),
    _primitiveType(primitiveType),
    _indexType(indexType),
    _vertexCount(0),
    _indexCount(0)
{
}

Mesh::Mesh(const Mesh& mesh) :
    _vertexLayout(mesh._vertexLayout),
    _primitiveType(mesh._primitiveType),
    _indexType(mesh._indexType),
    _vertexData(mesh._vertexData),
    _indexData(mesh._indexData),
    _vertexCount(mesh._vertexCount),
    _indexCount(mesh._indexCount),
    _boundingBox(mesh._boundingBox)
{
}

void Mesh::setVertexData(const VertexData& vertexData)
{
    if (_vertexData.size() > 0)
    {
        throw Error("Attempt to set the vertex data of a mesh with vertex data");
    }

    _vertexData = vertexData;
    _vertexCount = vertexData.size() / _vertexLayout.vertexSize();
}

const Mesh::VertexData& Mesh::vertexData() const
{
    return _vertexData;
}

size_t Mesh::vertexCount() const
{
    return _vertexCount;
}

void Mesh::setIndexData(const IndexData& indexData)
{
    if (_indexData.size() > 0)
    {
        throw Error("Attempt to set the index data of a mesh with index data");
    }

    _indexData = indexData;
    _indexCount = indexData.size() / indexSize();
}

const Mesh::IndexData& Mesh::indexData() const
{
    return _indexData;
}

size_t Mesh::indexCount() const
{
    return _indexCount;
}

unsigned Mesh::indexSize() const
{
    switch (_indexType)
    {
    case IndexType::UnsignedByte:
        return 1;
    case IndexType::UnsignedShort:
        return 2;
    case IndexType::UnsignedInt:
        return 4;
    }
    return 0;
}

const VertexLayout& Mesh::vertexLayout() const
{
    return _vertexLayout;
}

void Mesh::setVertexLayout(const VertexLayout& vertexLayout)
{
    if (_vertexData.size() > 0)
    {
        throw Error("Attempt to set the vertex layout of a mesh with vertex data");
    }

    _vertexLayout = vertexLayout;
}

PrimitiveType Mesh::primitiveType() const
{
    return _primitiveType;
}

void Mesh::setPrimitiveType(PrimitiveType primitiveType)
{
    _primitiveType = primitiveType;
}

IndexType Mesh::indexType() const
{
    return _indexType;
}

void Mesh::setIndexType(IndexType indexType)
{
    if (_indexData.size() > 0)
    {
        throw Error("Attempt to set the index type of a mesh with index data");
    }

    _indexType = indexType;
}

AxisAlignedBox<float>& Mesh::boundingBox()
{
    return _boundingBox;
}

const AxisAlignedBox<float>& Mesh::boundingBox() const
{
    return _boundingBox;
}