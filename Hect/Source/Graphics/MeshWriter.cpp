#include "Hect.h"

using namespace hect;

MeshWriter::MeshWriter(Mesh& mesh) :
    _mesh(&mesh),
    _vertexDataIndex(0)
{
}

size_t MeshWriter::addVertex()
{
    _vertexDataIndex = _mesh->_vertexData.size();

    // Push back zeroed data for the added vertex
    for (unsigned i = 0; i < _mesh->vertexLayout().vertexSize(); ++i)
    {
        _mesh->_vertexData.push_back(0);
    }

    return _mesh->_vertexCount++;
}

void MeshWriter::writeAttributeData(VertexAttributeSemantic semantic, float value)
{
    const VertexAttribute* attribute = _mesh->vertexLayout().attributeWithSemantic(semantic);
    if (attribute)
    {
        _setComponentValue(attribute, 0, value);
    }
}

void MeshWriter::writeAttributeData(VertexAttributeSemantic semantic, const Vector2<float>& value)
{
    const VertexAttribute* attribute = _mesh->vertexLayout().attributeWithSemantic(semantic);
    if (attribute)
    {
        VertexAttributeType type = attribute->type();
        unsigned cardinality = attribute->cardinality();

        // If the type matches and the cardinality is large enough then set it
        // all components at the same time
        if (type == VertexAttributeType::Float && cardinality >= 2)
        {
            _writeAttributeData(*attribute, value);
        }

        // Otherwise set each component individually
        else
        {
            if (cardinality > 0)
            {
                _setComponentValue(attribute, 0, value.x);
            }

            if (cardinality > 1)
            {
                _setComponentValue(attribute, 1, value.y);
            }
        }
    }
}

void MeshWriter::writeAttributeData(VertexAttributeSemantic semantic, const Vector3<float>& value)
{
    // If this data is a position then expand the bounding box to include it
    if (semantic == VertexAttributeSemantic::Position)
    {
        _mesh->boundingBox().expandToInclude(value);
    }

    const VertexAttribute* attribute = _mesh->vertexLayout().attributeWithSemantic(semantic);
    if (attribute)
    {
        VertexAttributeType type = attribute->type();
        unsigned cardinality = attribute->cardinality();

        // If the type matches and the cardinality is large enough then set it
        // all components at the same time
        if (type == VertexAttributeType::Float && cardinality >= 3)
        {
            _writeAttributeData(*attribute, value);
        }

        // Otherwise set each component individually
        else
        {
            if (cardinality > 0)
            {
                _setComponentValue(attribute, 0, value.x);
            }

            if (cardinality > 1)
            {
                _setComponentValue(attribute, 1, value.y);
            }

            if (cardinality > 2)
            {
                _setComponentValue(attribute, 2, value.z);
            }
        }
    }
}

void MeshWriter::writeAttributeData(VertexAttributeSemantic semantic, const Vector4<float>& value)
{
    const VertexAttribute* attribute = _mesh->vertexLayout().attributeWithSemantic(semantic);
    if (attribute)
    {
        VertexAttributeType type = attribute->type();
        unsigned cardinality = attribute->cardinality();

        // If the type matches and the cardinality is large enough then set it
        // all components at the same time
        if (type == VertexAttributeType::Float && cardinality >= 4)
        {
            _writeAttributeData(*attribute, value);
        }

        // Otherwise set each component individually
        else
        {
            if (cardinality > 0)
            {
                _setComponentValue(attribute, 0, value.x);
            }

            if (cardinality > 1)
            {
                _setComponentValue(attribute, 1, value.y);
            }

            if (cardinality > 2)
            {
                _setComponentValue(attribute, 2, value.z);
            }

            if (cardinality > 3)
            {
                _setComponentValue(attribute, 3, value.w);
            }
        }
    }
}

void MeshWriter::addIndex(uint64_t value)
{
    IndexType indexType = _mesh->indexType();
    size_t indexSize = _mesh->indexSize();

    // Push back zeroed data for the added index
    size_t indexDataIndex = _mesh->_indexData.size();
    for (unsigned i = 0; i < indexSize; ++i)
    {
        _mesh->_indexData.push_back(0);
    }

    // Get the location of the index
    void* index = &_mesh->_indexData[indexDataIndex];

    // Set the index data based on the type
    switch (indexType)
    {
    case IndexType::UnsignedByte:
        *(uint8_t*)index = (uint8_t)value;
        break;
    case IndexType::UnsignedShort:
        *(uint16_t*)index = (uint16_t)value;
        break;
    case IndexType::UnsignedInt:
        *(uint32_t*)index = (uint32_t)value;
        break;
    }

    ++_mesh->_indexCount;
}

void MeshWriter::_setComponentValue(const VertexAttribute* attribute, unsigned index, float value)
{
    size_t offset = _vertexDataIndex + attribute->offset();

    // Set the vertex data based on the type
    switch (attribute->type())
    {
    case VertexAttributeType::Half:
        throw Error("16-bit floats are not yet implemented");
        break;
    case VertexAttributeType::Float:
        *(float*)&_mesh->_vertexData[offset + index * 4] = value;
        break;
    }
}