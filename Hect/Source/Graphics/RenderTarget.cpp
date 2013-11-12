#include "Hect.h"

using namespace hect;

RenderTarget::RenderTarget() :
    _width(0),
    _height(0)
{
}

RenderTarget::RenderTarget(unsigned width, unsigned height) :
    _width(width),
    _height(height)
{
}

unsigned RenderTarget::width() const
{
    return _width;
}

unsigned RenderTarget::height() const
{
    return _height;
}

float RenderTarget::aspectRatio() const
{
    return (float)_width / (float)_height;
}

void RenderTarget::setWidth(unsigned width)
{
    _width = width;
}

void RenderTarget::setHeight(unsigned height)
{
    _height = height;
}