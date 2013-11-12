#include "Hect.h"

using namespace hect;

GpuObject::GpuObject() :
    _uploaded(false),
    _data(nullptr),
    _gpu(nullptr)
{
}

GpuObject::~GpuObject()
{
    if (_uploaded)
    {
        delete _data;
    }
}

bool GpuObject::isUploaded() const
{
    return _uploaded;
}

Gpu* GpuObject::gpu() const
{
    return _gpu;
}