#include "Hect.h"

using namespace hect;

Technique::Technique()
{
}

Technique::Technique(const Pass::Array& passes) :
    _passes(passes)
{
}

Pass::Array& Technique::passes()
{
    return _passes;
}

const Pass::Array& Technique::passes() const
{
    return _passes;
}