#include "Hect.h"

using namespace hect;

VertexLayout VertexLayout::createDefault()
{
    VertexAttribute::Array attributes;
    attributes.push_back(VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 3));
    attributes.push_back(VertexAttribute(VertexAttributeSemantic::Normal, VertexAttributeType::Float, 3));
    attributes.push_back(VertexAttribute(VertexAttributeSemantic::Tangent, VertexAttributeType::Float, 3));
    attributes.push_back(VertexAttribute(VertexAttributeSemantic::TextureCoords0, VertexAttributeType::Float, 2));

    return VertexLayout(attributes);
}

VertexLayout::VertexLayout() :
    _vertexSize(0)
{
}

VertexLayout::VertexLayout(const VertexAttribute::Array& attributes) :
    _attributes(attributes),
    _vertexSize(0)
{
    for (VertexAttribute& attribute : _attributes)
    {
        attribute._offset = _vertexSize;
        _vertexSize += attribute.size();
    }
}

const VertexAttribute* VertexLayout::attributeWithSemantic(VertexAttributeSemantic semantic) const
{
    const VertexAttribute* resultingAttribute = nullptr;
    for (const VertexAttribute& attribute : _attributes)
    {
        if (!resultingAttribute && attribute.semantic() == semantic)
        {
            resultingAttribute = &attribute;
        }
    }
    return resultingAttribute;
}

const VertexAttribute::Array& VertexLayout::attributes() const
{
    return _attributes;
}

unsigned VertexLayout::vertexSize() const
{
    return _vertexSize;
}