#include "Hect.h"

using namespace hect;

Pass::Pass(const RenderMode& renderMode, const Texture::RefArray& textures, Shader::Ref shader, const Shader::Argument::Array& shaderArguments) :
    _renderMode(renderMode),
    _textures(textures),
    _shader(shader),
    _shaderArguments(shaderArguments)
{
    assert(shader);
    _resolveShaderArguments();
}

void Pass::prepare(Gpu& gpu) const
{
    // Bind the render mode
    gpu.bindMode(_renderMode);

    // Bind the textures in the pass
    unsigned textureIndex = 0;
    for (const Texture::Ref& texture : _textures)
    {
        if (texture)
        {
            gpu.bindTexture(*texture, textureIndex);
        }
        ++textureIndex;
    }

    // Bind the shader
    gpu.bindShader(*_shader);

    // Set the shader arguments
    for (auto& pair : _resolvedArguments)
    {
        const Shader::Parameter& parameter = *pair.first;
        const Shader::Value& value = pair.second;
        gpu.setShaderParameter(parameter, value);
    }
}

RenderMode& Pass::renderMode()
{
    return _renderMode;
}

const RenderMode& Pass::renderMode() const
{
    return _renderMode;
}

const Texture::RefArray& Pass::textures() const
{
    return _textures;
}

const Shader::Ref& Pass::shader() const
{
    return _shader;
}

const Shader::Argument::Array& Pass::shaderArguments() const
{
    return _shaderArguments;
}

void Pass::_resolveShaderArguments()
{
    assert(_shader);

    // Resolve the parameters that the arguments refer to (this would be
    // invalidated if the shader changes)
    for (const Shader::Argument& argument : _shaderArguments)
    {
        const Shader::Parameter& parameter = _shader->parameterWithName(argument.parameterName());
        _resolvedArguments[&parameter] = argument.value();
    }
}