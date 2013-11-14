#include "Hect.h"

using namespace hect;

ShaderModule::ShaderModule() :
    _type(Vertex)
{
}

ShaderModule::~ShaderModule()
{
    if (isUploaded())
    {
        gpu()->destroyShaderModule(*this);
    }
}

ShaderModule::ShaderModule(Type type, const std::string& source) :
    _type(type),
    _source(source)
{
}

ShaderModule::Type ShaderModule::type() const
{
    return _type;
}

const std::string& ShaderModule::source() const
{
    return _source;
}