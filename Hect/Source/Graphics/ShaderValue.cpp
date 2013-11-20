#include "Hect.h"

using namespace hect;

ShaderValue::ShaderValue() :
    _type(ShaderValueType::Float)
{
}

ShaderValue::ShaderValue(ShaderValueType type) :
    _type(type)
{
}

ShaderValue::ShaderValue(int value, ShaderValueType type) :
    _type(type)
{
    if (type != ShaderValueType::Int && type != ShaderValueType::Texture)
    {
        throw Error("Invalid shader value type");
    }

    setValue(value);
}

ShaderValue::ShaderValue(float value) :
    _type(ShaderValueType::Float)
{
    setValue(value);
}

ShaderValue::ShaderValue(const Vector2<float>& value) :
    _type(ShaderValueType::Vector2)
{
    setValue(value);
}

ShaderValue::ShaderValue(const Vector3<float>& value) :
    _type(ShaderValueType::Vector3)
{
    setValue(value);
}

ShaderValue::ShaderValue(const Vector4<float>& value) :
    _type(ShaderValueType::Vector4)
{
    setValue(value);
}

ShaderValue::ShaderValue(const Matrix4<float>& value) :
    _type(ShaderValueType::Matrix4)
{
    setValue(value);
}

ShaderValueType ShaderValue::type() const
{
    return _type;
}

const void* ShaderValue::data() const
{
    return &_value;
}

void ShaderValue::setValue(int value)
{
    if (_type != ShaderValueType::Int && _type != ShaderValueType::Texture)
    {
        throw Error("Shader value is not of type 'Int'");
    }

    _value.intValue = value;
}

void ShaderValue::setValue(float value)
{
    if (_type != ShaderValueType::Float)
    {
        throw Error("Shader value is not of type 'Float'");
    }

    _value.floatValues[0] = value;
}

void ShaderValue::setValue(const Vector2<float>& value)
{
    if (_type != ShaderValueType::Vector2)
    {
        throw Error("Shader value is not of type 'Vector2'");
    }

    *(hect::Vector2<float>*)&_value = value;
}

void ShaderValue::setValue(const Vector3<float>& value)
{
    if (_type != ShaderValueType::Vector3)
    {
        throw Error("Shader value is not of type 'Vector3'");
    }

    *(hect::Vector3<float>*)&_value = value;
}

void ShaderValue::setValue(const Vector4<float>& value)
{
    if (_type != ShaderValueType::Vector4)
    {
        throw Error("Shader value is not of type 'Vector4'");
    }

    *(hect::Vector4<float>*)&_value = value;
}

void ShaderValue::setValue(const Matrix4<float>& value)
{
    if (_type != ShaderValueType::Matrix4)
    {
        throw Error("Shader value is not of type 'Matrix4'");
    }

    *(hect::Matrix4<float>*)&_value = value;
}