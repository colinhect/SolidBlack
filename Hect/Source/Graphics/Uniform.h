#pragma once

namespace hect
{

///
/// A binding from a shader uniform variable to a built-in value in the
/// rendering pipeline.
enum class UniformBinding
{
    ///
    /// No binding.
    None,

    ///
    /// Bound to the size of the active render target.
    RenderTargetSize,

    ///
    /// Bound to the world-space position of the active camera.
    CameraPosition,

    ///
    /// Bound to the world-space up direction of the active camera.
    CameraUp,

    ///
    /// Bound to the view matrix.
    ViewMatrix,

    ///
    /// Bound to the projection matrix.
    ProjectionMatrix,

    ///
    /// Bound to the product of the view and projection matrices.
    ViewProjectionMatrix,

    ///
    /// Bound to the model matrix.
    ModelMatrix,

    ///
    /// Bound to the product of the model and the view matrix.
    ModelViewMatrix,

    ///
    /// Bound to the product of the model, view, and projection matrices.
    ModelViewProjectionMatrix
};

///
/// A global variable of a shader which serves as parameter.
class Uniform
{
public:

    ///
    /// An array of uniforms.
    typedef std::vector<Uniform> Array;

    ///
    /// Constructs a uniform given its name and type.
    ///
    /// \param name The name.
    /// \param type The type.
    Uniform(const std::string& name, UniformType type);

    ///
    /// Constructs a uniform given its name and binding
    ///
    /// \param name The name.
    /// \param binding The binding.
    Uniform(const std::string& name, UniformBinding binding);

    ///
    /// Constructs a uniform given its name and default value.
    ///
    /// \param name The name.
    /// \param defaultValue The default value which will be set when the shader
    /// is bound (see Gpu::bindShader()).
    Uniform(const std::string& name, const UniformValue& defaultValue);

    ///
    /// Returns the uniform type.
    UniformType type() const;

    ///
    /// Returns the uniform binding.
    UniformBinding binding() const;

    ///
    /// Returns whether the uniform has a binding.
    bool hasBinding() const;

    ///
    /// Returns the default value.
    const UniformValue& defaultValue() const;

    ///
    /// Returns whether the uniform has a default value.
    bool hasDefaultValue() const;

    ///
    /// Returns the name of the uniform.
    const std::string& name() const;

    ///
    /// Returns the compiled location.
    int location() const;

    ///
    /// Sets the compiled location.
    ///
    /// \param location The compiled location.
    void setLocation(int location);

private:
    std::string _name;

    UniformType _type;

    UniformBinding _binding;

    bool _defaultValueSet;
    UniformValue _defaultValue;

    int _location;
};

}