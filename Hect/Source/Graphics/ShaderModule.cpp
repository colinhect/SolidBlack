#include "Hect.h"

using namespace hect;

ShaderModule::ShaderModule() :
    _type(ShaderModuleType::Vertex)
{
}

ShaderModule::ShaderModule(const std::string& name, ShaderModuleType type, const std::string& source) :
    _name(name),
    _type(type),
    _source(source)
{
}

ShaderModule::~ShaderModule()
{
    if (isUploaded())
    {
        renderer()->destroyShaderModule(*this);
    }
}

const std::string& ShaderModule::name() const
{
    return _name;
}

ShaderModuleType ShaderModule::type() const
{
    return _type;
}

const std::string& ShaderModule::source() const
{
    return _source;
}