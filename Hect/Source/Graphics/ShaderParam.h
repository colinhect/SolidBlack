#pragma once

namespace hect
{

///
/// A semantic binding to a built-in value.
enum class ShaderParamBinding
{
    ///
    /// No binding.
    None,

    ///
    /// Bound to the size of the active render target.
    RenderTargetSize,

    ///
    /// Bound to the position of the active camera.
    CameraPosition,

    ///
    /// Bound to the up direction of the active camera.
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
/// A parameter to a shader.
class ShaderParam
{
public:

    ///
    /// An array of parameters.
    typedef std::vector<ShaderParam> Array;

    ///
    /// Constructs a parameter given a name and a type.
    ///
    /// \param name The name.
    /// \param type The type.
    ShaderParam(const std::string& name, ShaderValueType type);
    ///
    /// Constructs a parameter given a name and a binding
    ///
    /// \param name The name.
    /// \param binding The binding.
    ShaderParam(const std::string& name, ShaderParamBinding binding);

    ///
    /// Constructs a parameter given a name an a default value.
    ///
    /// \param name The name.
    /// \param defaultValue The default value.
    ShaderParam(const std::string& name, const ShaderValue& defaultValue);

    ///
    /// Returns the value type that parameter is.
    ShaderValueType type() const;

    ///
    /// Returns the binding.
    ShaderParamBinding binding() const;

    ///
    /// Returns whether the parameter has a binding.
    bool hasBinding() const;

    ///
    /// Returns the default value.
    const ShaderValue& defaultValue() const;

    ///
    /// Returns whether the parameter has a default value.
    bool hasDefaultValue() const;

    ///
    /// Returns the name of the parameter.
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

    ShaderValueType _type;

    ShaderParamBinding _binding;

    bool _defaultValueSet;
    ShaderValue _defaultValue;

    int _location;
};

}