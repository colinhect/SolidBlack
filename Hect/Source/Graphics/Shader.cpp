#include "Hect.h"

using namespace hect;

Shader::Shader()
{
}

Shader::Shader(const ShaderModule::RefArray& modules, const ShaderParam::Array& params) :
    _modules(modules),
    _params(params)
{
}

Shader::~Shader()
{
    if (isUploaded())
    {
        gpu()->destroyShader(*this);
    }
}

const ShaderModule::RefArray& Shader::modules() const
{
    return _modules;
}

ShaderParam::Array& Shader::params()
{
    return _params;
}

const ShaderParam::Array& Shader::params() const
{
    return _params;
}

const ShaderParam& Shader::paramWithName(const std::string& name) const
{
    for (const ShaderParam& param : _params)
    {
        if (param.name() == name)
        {
            return param;
        }
    }

    throw Error(format("Shader does not have parameter '%s'", name.c_str()));
}
