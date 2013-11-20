#include "Hect.h"

using namespace hect;

RenderMode::RenderMode() :
    _stateBits(RenderState::DepthTest | RenderState::CullFace),
    _sourceFactor(BlendFactor::One),
    _destFactor(BlendFactor::One)
{
}

void RenderMode::enableState(RenderState state)
{
    _stateBits |= state;
}

void RenderMode::disableState(RenderState state)
{
    _stateBits &= ~state;
}

bool RenderMode::isStateEnabled(RenderState state) const
{
    return (_stateBits & state) == state;
}

void RenderMode::setBlendFactors(BlendFactor sourceFactor, BlendFactor destFactor)
{
    _sourceFactor = sourceFactor;
    _destFactor = destFactor;
}

BlendFactor RenderMode::sourceBlendFactor() const
{
    return _sourceFactor;
}

BlendFactor RenderMode::destBlendFactor() const
{
    return _destFactor;
}