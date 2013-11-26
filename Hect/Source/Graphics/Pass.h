#pragma once

namespace hect
{

///
/// A step in a material technique.
///
/// \remarks Contains the render mode, textures, shader, and uniform values
/// used when rendering geometry for this step in the technique.
class Pass
{
public:

    ///
    /// An array of passes.
    typedef std::vector<Pass> Array;

    ///
    /// Constructs a pass.
    ///
    /// \param renderMode The render mode that pass will bind.
    /// \param textures The textures that the pass will bind.
    /// \param shader The shader that the pass will bind.
    /// \param uniformValues The values for the uniforms in the shader.
    Pass(const RenderMode& renderMode, const Texture::RefArray& textures, Shader::Ref shader, const PassUniformValue::Array& uniformValues);

    ///
    /// Prepares a renderer to begin using this pass.
    ///
    /// \param renderer The renderer to prepare.
    void prepare(Renderer& renderer) const;

    ///
    /// Returns the render mode.
    RenderMode& renderMode();

    ///
    /// Returns the render mode.
    const RenderMode& renderMode() const;

    ///
    /// Returns the textures.
    const Texture::RefArray& textures() const;

    ///
    /// Returns the shader.
    const Shader::Ref& shader() const;

    ///
    /// Returns the uniform values.
    const PassUniformValue::Array& uniformValues() const;

private:

    // Resolves which uniforms the uniform values apply to for fast
    // binding
    void _resolvePassUniformValues();

    RenderMode _renderMode;
    Texture::RefArray _textures;
    Shader::Ref _shader;

    PassUniformValue::Array _uniformValues;
    std::map<const Uniform*, UniformValue> _resolvedUniformValues;
};

}