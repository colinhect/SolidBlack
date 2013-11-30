#include "Hect.h"

using namespace hect;

FrameBuffer::FrameBuffer() :
    _depthComponent(false)
{
}

FrameBuffer::FrameBuffer(const Texture::Array& targets, bool depthComponent) :
    _depthComponent(depthComponent),
    _targets(targets)
{
    unsigned width = 0;
    unsigned height = 0;

    for (Texture& target : _targets)
    {
        width = std::max(width, target.width());
        height = std::max(height, target.height());
    }

    setWidth(width);
    setHeight(height);
}

FrameBuffer::~FrameBuffer()
{
    if (isUploaded())
    {
        renderer()->destroyFrameBuffer(*this);
    }
}

void FrameBuffer::bind(Renderer* renderer)
{
    renderer->bindFrameBuffer(*this);
}

Texture::Array& FrameBuffer::targets()
{
    return _targets;
}

const Texture::Array& FrameBuffer::targets() const
{
    return _targets;
}

bool FrameBuffer::hasDepthComponent() const
{
    return _depthComponent;
}