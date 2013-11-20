#pragma once

namespace hect
{

///
/// The type of a value for a shader parameter.
enum class ShaderValueType
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
/// A value for a shader parameter.
class ShaderValue
{
public:

    ///
    /// Constructs a default parameter value.
    ShaderValue();

    ///
    /// Constructs a parameter value given its type.
    ///
    /// \param type The type.
    ShaderValue(ShaderValueType type);

    ///
    /// Constructs an integer based parameter value given its the integer value
    /// and its type.
    ///
    /// \param value The integer value.
    /// \param type The type.
    ShaderValue(int value, ShaderValueType type);

    ///
    /// Constructs a float parameter value.
    ///
    /// \param value The value.
    ShaderValue(float value);

    ///
    /// Constructs a 2-dimensional vector parameter value.
    ///
    /// \param value The value.
    ShaderValue(const Vector2<float>& value);

    ///
    /// Constructs a 3-dimensional vector parameter value.
    ///
    /// \param value The value.
    ShaderValue(const Vector3<float>& value);

    ///
    /// Constructs a 4-dimensional vector parameter value.
    ///
    /// \param value The value.
    ShaderValue(const Vector4<float>& value);

    ///
    /// Constructs a 4 by 4 matrix parameter value.
    ///
    /// \param value The value.
    ShaderValue(const hect::Matrix4<float>& value);

    ///
    /// Returns the type.
    ShaderValueType type() const;

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
    void setValue(const Vector2<float>& value);

    ///
    /// Sets the value of the parameter value as a 3-dimensional vector.
    ///
    /// \param value The value.
    void setValue(const Vector3<float>& value);

    ///
    /// Sets the value of the parameter value as a 4-dimensional vector.
    ///
    /// \param value The value.
    void setValue(const Vector4<float>& value);

    ///
    /// Sets the value of the parameter value as a 4 by 4 matrix.
    ///
    /// \param value The value.
    void setValue(const Matrix4<float>& value);

private:
    ShaderValueType _type;

    union
    {
        int intValue;
        float floatValues[16];
    } _value;
};

}