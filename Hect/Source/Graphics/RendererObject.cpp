#include "Hect.h"

using namespace hect;

RendererObject::RendererObject() :
    _uploaded(false),
    _data(nullptr),
    _renderer(nullptr)
{
}

RendererObject::~RendererObject()
{
    if (_uploaded)
    {
        delete _data;
    }
}

bool RendererObject::isUploaded() const
{
    return _uploaded;
}

Renderer* RendererObject::renderer() const
{
    return _renderer;
}