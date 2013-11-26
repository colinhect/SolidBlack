#include "Hect.h"

using namespace hect;

ShaderModule::ShaderModule() :
    _type(ShaderModuleType::Vertex)
{
}

ShaderModule::~ShaderModule()
{
    if (isUploaded())
    {
        renderer()->destroyShaderModule(*this);
    }
}

ShaderModule::ShaderModule(ShaderModuleType type, const std::string& source) :
    _type(type),
    _source(source)
{
}

ShaderModuleType ShaderModule::type() const
{
    return _type;
}

const std::string& ShaderModule::source() const
{
    return _source;
}