namespace hect
{

///
/// A step in a material technique.
///
/// \remarks Contains the render mode, textures, shader, and shader arguments
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
    /// \param shaderArguments The argument values for the parameters in the
    /// shader.
    Pass(const RenderMode& renderMode, const Texture::RefArray& textures, Shader::Ref shader, const Shader::Argument::Array& shaderArguments);

    ///
    /// Prepares a GPU to begin using this pass.
    ///
    /// \param gpu The GPU to prepare.
    void prepare(Gpu& gpu) const;

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
    /// Returns the shader arguments.
    const Shader::Argument::Array& shaderArguments() const;

private:

    // Resolves which shader parameters the shader arguments apply to for fast
    // binding
    void _resolveShaderArguments();

    RenderMode _renderMode;
    Texture::RefArray _textures;
    Shader::Ref _shader;

    Shader::Argument::Array _shaderArguments;
    std::map<const Shader::Parameter*, Shader::Value> _resolvedArguments;
};

}