#include "Hect.h"

using namespace hect;

VertexAttribute::VertexAttribute(Semantic semantic, Type type, unsigned cardinality) :
    _semantic(semantic),
    _type(type),
    _cardinality(cardinality),
    _offset(0)
{
}

VertexAttribute::Semantic VertexAttribute::semantic() const
{
    return _semantic;
}

VertexAttribute::Type VertexAttribute::type() const
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
    case Float16:
        return 2 * _cardinality;
    case Float32:
        return 4 * _cardinality;
    }

    return 0;
}

unsigned VertexAttribute::offset() const
{
    return _offset;
}