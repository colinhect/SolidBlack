#include "Hect.h"

using namespace hect;

Shader::Shader()
{
}

Shader::Shader(const ShaderModule::RefArray& modules, const Uniform::Array& uniforms) :
    _modules(modules),
    _uniforms(uniforms)
{
}

Shader::~Shader()
{
    if (isUploaded())
    {
        renderer()->destroyShader(*this);
    }
}

const ShaderModule::RefArray& Shader::modules() const
{
    return _modules;
}

Uniform::Array& Shader::uniforms()
{
    return _uniforms;
}

const Uniform::Array& Shader::uniforms() const
{
    return _uniforms;
}

const Uniform& Shader::uniformWithName(const std::string& name) const
{
    for (const Uniform& uniform : _uniforms)
    {
        if (uniform.name() == name)
        {
            return uniform;
        }
    }

    throw Error(format("Shader does not have uniform '%s'", name.c_str()));
}
