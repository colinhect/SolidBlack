#include "Hect.h"

using namespace hect;

Pass::Pass(const RenderMode& renderMode, const AssetHandle<Texture>::Array& textures, const AssetHandle<Shader>& shader, const PassUniformValue::Array& uniformValues) :
    _renderMode(renderMode),
    _textures(textures),
    _shader(shader),
    _uniformValues(uniformValues)
{
    _resolvePassUniformValues();
}

void Pass::prepare(Renderer& renderer) const
{
    // Bind the render mode
    renderer.bindMode(_renderMode);

    // Bind the textures in the pass
    unsigned textureIndex = 0;
    for (const AssetHandle<Texture>& texture : _textures)
    {
        renderer.bindTexture(texture.get(), textureIndex);
        ++textureIndex;
    }

    // Bind the shader
    renderer.bindShader(_shader.get());

    // Set the uniform values
    for (auto& pair : _resolvedUniformValues)
    {
        const Uniform& uniform = *pair.first;
        const UniformValue& value = pair.second;
        renderer.setUniform(uniform, value);
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

const AssetHandle<Texture>::Array& Pass::textures() const
{
    return _textures;
}

const AssetHandle<Shader>& Pass::shader() const
{
    return _shader;
}

const PassUniformValue::Array& Pass::uniformValues() const
{
    return _uniformValues;
}

void Pass::_resolvePassUniformValues()
{
    // Resolve the uniforms that the uniform values refer to (this would be
    // invalidated if the shader changes)
    for (const PassUniformValue& uniformValue : _uniformValues)
    {
        const Uniform& uniform = _shader.get().uniformWithName(uniformValue.uniformName());
        _resolvedUniformValues[&uniform] = uniformValue.value();
    }
}