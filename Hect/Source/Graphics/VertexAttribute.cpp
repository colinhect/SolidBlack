#include "Hect.h"

using namespace hect;

VertexAttribute::VertexAttribute(VertexAttributeSemantic semantic, VertexAttributeType type, unsigned cardinality) :
    _semantic(semantic),
    _type(type),
    _cardinality(cardinality),
    _offset(0)
{
}

VertexAttributeSemantic VertexAttribute::semantic() const
{
    return _semantic;
}

VertexAttributeType VertexAttribute::type() const
{
    return _type;
}

unsigned VertexAttribute::cardinality() const
{
    return _cardinality;
}

unsigned VertexAttribute::size() const
{
    switch (_type)
    {
    case VertexAttributeType::Half:
        return 2 * _cardinality;
    case VertexAttributeType::Float:
        return 4 * _cardinality;
    }

    return 0;
}

unsigned VertexAttribute::offset() const
{
    return _offset;
}