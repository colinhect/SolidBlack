#pragma once

namespace hect
{

///
/// A GPU shader program.
class Shader :
    public GpuObject
{
public:

    ///
    /// A value for a shader parameter.
    class Value
    {
    public:

        ///
        /// The type of a value for a shader parameter.
        enum Type
        {
            ///
            /// An integer.
            Int,

            ///
            /// A floating point number.
            Float,

            ///
            /// A 2-dimensional vector.
            Vector2,

            ///
            /// A 3-dimensional vector.
            Vector3,

            ///
            /// A 4-dimensional vector.
            Vector4,

            ///
            /// A 4 by 4 matrix.
            Matrix4,

            ///
            /// A texture (the index of the texture).
            Texture
        };

        ///
        /// Constructs a default parameter value.
        Value();

        ///
        /// Constructs a parameter value given its type.
        ///
        /// \param type The type.
        Value(Type type);

        ///
        /// Constructs an integer based parameter value given its the integer value
        /// and its type.
        ///
        /// \param value The integer value.
        /// \param type The type.
        Value(int value, Type type);

        ///
        /// Constructs a float parameter value.
        ///
        /// \param value The value.
        Value(float value);

        ///
        /// Constructs a 2-dimensional vector parameter value.
        ///
        /// \param value The value.
        Value(const hect::Vector2<float>& value);

        ///
        /// Constructs a 3-dimensional vector parameter value.
        ///
        /// \param value The value.
        Value(const hect::Vector3<float>& value);

        ///
        /// Constructs a 4-dimensional vector parameter value.
        ///
        /// \param value The value.
        Value(const hect::Vector4<float>& value);

        ///
        /// Constructs a 4 by 4 matrix parameter value.
        ///
        /// \param value The value.
        Value(const hect::Matrix4<float>& value);

        ///
        /// Returns the type.
        Type type() const;

        ///
        /// Returns the raw data.
        const void* data() const;

        ///
        /// Sets the value of the parameter value as an integer.
        ///
        /// \param value The value.
        void setValue(int value);

        ///
        /// Sets the value of the parameter value as a float.
        ///
        /// \param value The value.
        void setValue(float value);

        ///
        /// Sets the value of the parameter value as a 2-dimensional vector.
        ///
        /// \param value The value.
        void setValue(const hect::Vector2<float>& value);

        ///
        /// Sets the value of the parameter value as a 3-dimensional vector.
        ///
        /// \param value The value.
        void setValue(const hect::Vector3<float>& value);

        ///
        /// Sets the value of the parameter value as a 4-dimensional vector.
        ///
        /// \param value The value.
        void setValue(const hect::Vector4<float>& value);

        ///
        /// Sets the value of the parameter value as a 4 by 4 matrix.
        ///
        /// \param value The value.
        void setValue(const hect::Matrix4<float>& value);

    private:
        Type _type;

        union
        {
            int intValue;
            float floatValues[16];
        } _value;
    };

    ///
    /// A parameter to a shader.
    class Parameter
    {
    public:

        ///
        /// An array of parameters.
        typedef std::vector<Parameter> Array;

        ///
        /// A semantic binding to a built-in value.
        enum Binding
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
        /// Constructs a parameter given a name and a type.
        ///
        /// \param name The name.
        /// \param type The type.
        Parameter(const std::string& name, Shader::Value::Type type);
        ///
        /// Constructs a parameter given a name and a binding
        ///
        /// \param name The name.
        /// \param binding The binding.
        Parameter(const std::string& name, Binding binding);

        ///
        /// Constructs a parameter given a name an a default value.
        ///
        /// \param name The name.
        /// \param defaultValue The default value.
        Parameter(const std::string& name, const Shader::Value& defaultValue);

        ///
        /// Returns the value type that parameter is.
        Shader::Value::Type type() const;

        ///
        /// Returns the binding.
        Binding binding() const;

        ///
        /// Returns whether the parameter has a binding.
        bool hasBinding() const;

        ///
        /// Returns the default value.
        const Shader::Value& defaultValue() const;

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

        Shader::Value::Type _type;

        Binding _binding;

        bool _defaultValueSet;
        Shader::Value _defaultValue;

        int _location;
    };

    ///
    /// A value for a parameter.
    class Argument
    {
    public:

        ///
        /// An array of arguments.
        typedef std::vector<Argument> Array;

        ///
        /// Constructs an argument given a name an a value.
        ///
        /// \param parameterName The name of the parameter.
        /// \param value The default value.
        Argument(const std::string& parameterName, const Shader::Value& value);

        ///
        /// Returns the name of the parameter.
        const std::string& parameterName() const;

        ///
        /// Returns the value.
        const Shader::Value& value() const;

    private:
        std::string _parameterName;
        Shader::Value _value;
    };

    ///
    /// A shared reference to a shader.
    typedef std::shared_ptr<Shader> Ref;

    ///
    /// Constructs a shader without any modules or parameter values.
    Shader();

    ///
    /// Constructs a shader given its modules and parameter.
    ///
    /// \param modules The modules.
    /// \param parameters The parameters.
    Shader(const ShaderModule::RefArray& modules, const Parameter::Array& parameters);

    ///
    /// Destroys the shader if it is uploaded.
    ~Shader();

    ///
    /// Returns the modules.
    const ShaderModule::RefArray& modules() const;

    ///
    /// Returns the parameters.
    Parameter::Array& parameters();

    ///
    /// Returns the parameters.
    const Parameter::Array& parameters() const;

    ///
    /// Returns the parameter with the given name.
    ///
    /// \param name The name of the parameter.
    ///
    /// \throws Error If no parameter with the given name exists.
    const Parameter& parameterWithName(const std::string& name) const;

private:
    ShaderModule::RefArray _modules;
    Parameter::Array _parameters;
};

}