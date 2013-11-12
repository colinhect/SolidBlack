#include "Hect.h"

using namespace hect;

VertexLayout VertexLayout::createDefault()
{
    VertexAttribute::Array attributes;
    attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float32, 3));
    attributes.push_back(VertexAttribute(VertexAttribute::Normal, VertexAttribute::Float32, 3));
    attributes.push_back(VertexAttribute(VertexAttribute::Tangent, VertexAttribute::Float32, 3));
    attributes.push_back(VertexAttribute(VertexAttribute::TextureCoords0, VertexAttribute::Float32, 2));

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

const VertexAttribute* VertexLayout::attributeWithSemantic(VertexAttribute::Semantic semantic) const
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