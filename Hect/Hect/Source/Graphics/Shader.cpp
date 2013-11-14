#include "Hect.h"

using namespace hect;

Shader::Value::Value() :
    _type(Float)
{
}

Shader::Value::Value(Type type) :
    _type(type)
{
}

Shader::Value::Value(int value, Type type) :
    _type(type)
{
    if (type != Int && type != Texture)
    {
        throw Error("Invalid parameter value type");
    }

    setValue(value);
}

Shader::Value::Value(float value) :
    _type(Float)
{
    setValue(value);
}

Shader::Value::Value(const hect::Vector2<float>& value) :
    _type(Vector2)
{
    setValue(value);
}

Shader::Value::Value(const hect::Vector3<float>& value) :
    _type(Vector3)
{
    setValue(value);
}

Shader::Value::Value(const hect::Vector4<float>& value) :
    _type(Vector4)
{
    setValue(value);
}

Shader::Value::Value(const hect::Matrix4<float>& value) :
    _type(Matrix4)
{
    setValue(value);
}

Shader::Value::Type Shader::Value::type() const
{
    return _type;
}

const void* Shader::Value::data() const
{
    return &_value;
}

void Shader::Value::setValue(int value)
{
    if (_type != Int && _type != Texture)
    {
        throw Error("Shader value is not of type 'Int'");
    }

    _value.intValue = value;
}

void Shader::Value::setValue(float value)
{
    if (_type != Float)
    {
        throw Error("Shader value is not of type 'Float'");
    }

    _value.floatValues[0] = value;
}

void Shader::Value::setValue(const hect::Vector2<float>& value)
{
    if (_type != Vector2)
    {
        throw Error("Shader value is not of type 'Vector2'");
    }

    *(hect::Vector2<float>*)&_value = value;
}

void Shader::Value::setValue(const hect::Vector3<float>& value)
{
    if (_type != Vector3)
    {
        throw Error("Shader value is not of type 'Vector3'");
    }

    *(hect::Vector3<float>*)&_value = value;
}

void Shader::Value::setValue(const hect::Vector4<float>& value)
{
    if (_type != Vector4)
    {
        throw Error("Shader value is not of type 'Vector4'");
    }

    *(hect::Vector4<float>*)&_value = value;
}

void Shader::Value::setValue(const hect::Matrix4<float>& value)
{
    if (_type != Matrix4)
    {
        throw Error("Shader value is not of type 'Matrix4'");
    }

    *(hect::Matrix4<float>*)&_value = value;
}


Shader::Parameter::Parameter(const std::string& name, Value::Type type) :
    _name(name),
    _type(type),
    _binding(None),
    _defaultValueSet(false),
    _location(-1)
{
}

Shader::Parameter::Parameter(const std::string& name, Binding binding) :
    _name(name),
    _type(Value::Float),
    _binding(binding),
    _defaultValueSet(false),
    _location(-1)
{
    switch (binding)
    {
    case RenderTargetSize:
        _type = Value::Vector2;
        break;
    case CameraPosition:
    case CameraUp:
        _type = Value::Vector3;
        break;
    case ViewMatrix:
    case ProjectionMatrix:
    case ViewProjectionMatrix:
    case ModelMatrix:
    case ModelViewMatrix:
    case ModelViewProjectionMatrix:
        _type = Value::Matrix4;
        break;
    }
}

Shader::Parameter::Parameter(const std::string& name, const Value& defaultValue) :
    _name(name),
    _type(defaultValue.type()),
    _binding(None),
    _defaultValueSet(true),
    _defaultValue(defaultValue),
    _location(-1)
{
}

Shader::Value::Type Shader::Parameter::type() const
{
    return _type;
}

Shader::Parameter::Binding Shader::Parameter::binding() const
{
    return _binding;
}

bool Shader::Parameter::hasBinding() const
{
    return _binding != None;
}

const Shader::Value& Shader::Parameter::defaultValue() const
{
    return _defaultValue;
}

bool Shader::Parameter::hasDefaultValue() const
{
    return _defaultValueSet;
}

const std::string& Shader::Parameter::name() const
{
    return _name;
}

int Shader::Parameter::location() const
{
    return _location;
}

void Shader::Parameter::setLocation(int location)
{
    _location = location;
}

Shader::Argument::Argument(const std::string& parameterName, const Value& value) :
    _parameterName(parameterName),
    _value(value)
{
}

const std::string& Shader::Argument::parameterName() const
{
    return _parameterName;
}

const Shader::Value& Shader::Argument::value() const
{
    return _value;
}

Shader::Shader()
{
}

Shader::Shader(const ShaderModule::RefArray& modules, const Parameter::Array& parameters) :
    _modules(modules),
    _parameters(parameters)
{
}

Shader::~Shader()
{
    if (isUploaded())
    {
        gpu()->destroyShader(*this);
    }
}

const ShaderModule::RefArray& Shader::modules() const
{
    return _modules;
}

Shader::Parameter::Array& Shader::parameters()
{
    return _parameters;
}

const Shader::Parameter::Array& Shader::parameters() const
{
    return _parameters;
}

const Shader::Parameter& Shader::parameterWithName(const std::string& name) const
{
    for (const Parameter& parameter : _parameters)
    {
        if (parameter.name() == name)
        {
            return parameter;
        }
    }

    throw Error(format("Shader does not have parameter '%s'", name.c_str()));
}
