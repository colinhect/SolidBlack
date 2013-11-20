#include "Hect.h"

using namespace hect;

Pass::Pass(const RenderMode& renderMode, const Texture::RefArray& textures, Shader::Ref shader, const ShaderArg::Array& shaderArgs) :
    _renderMode(renderMode),
    _textures(textures),
    _shader(shader),
    _shaderArgs(shaderArgs)
{
    assert(shader);
    _resolveShaderArgs();
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
    for (auto& pair : _resolvedArgs)
    {
        const ShaderParam& param = *pair.first;
        const ShaderValue& value = pair.second;
        gpu.setShaderParam(param, value);
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

const ShaderArg::Array& Pass::shaderArgs() const
{
    return _shaderArgs;
}

void Pass::_resolveShaderArgs()
{
    assert(_shader);

    // Resolve the parameters that the arguments refer to (this would be
    // invalidated if the shader changes)
    for (const ShaderArg& arg : _shaderArgs)
    {
        const ShaderParam& param = _shader->paramWithName(arg.paramName());
        _resolvedArgs[&param] = arg.value();
    }
}