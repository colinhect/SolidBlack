#include "Hect.h"

using namespace hect;

RenderMode::RenderMode() :
    _stateBits(DepthTest | CullFace),
    _sourceFactor(One),
    _destFactor(One)
{
}

void RenderMode::enableState(State state)
{
    _stateBits |= state;
}

void RenderMode::disableState(State state)
{
    _stateBits &= ~state;
}

bool RenderMode::isStateEnabled(State state) const
{
    return (_stateBits & state) == state;
}

void RenderMode::setBlendFactors(BlendFactor sourceFactor, BlendFactor destFactor)
{
    _sourceFactor = sourceFactor;
    _destFactor = destFactor;
}

RenderMode::BlendFactor RenderMode::sourceBlendFactor() const
{
    return _sourceFactor;
}

RenderMode::BlendFactor RenderMode::destBlendFactor() const
{
    return _destFactor;
}