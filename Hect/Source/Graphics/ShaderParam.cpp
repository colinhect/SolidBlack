#include "Hect.h"

using namespace hect;

ShaderParam::ShaderParam(const std::string& name, ShaderValueType type) :
    _name(name),
    _type(type),
    _binding(ShaderParamBinding::None),
    _defaultValueSet(false),
    _location(-1)
{
}

ShaderParam::ShaderParam(const std::string& name, ShaderParamBinding binding) :
    _name(name),
    _type(ShaderValueType::Float),
    _binding(binding),
    _defaultValueSet(false),
    _location(-1)
{
    switch (binding)
    {
    case ShaderParamBinding::RenderTargetSize:
        _type = ShaderValueType::Vector2;
        break;
    case ShaderParamBinding::CameraPosition:
    case ShaderParamBinding::CameraUp:
        _type = ShaderValueType::Vector3;
        break;
    case ShaderParamBinding::ViewMatrix:
    case ShaderParamBinding::ProjectionMatrix:
    case ShaderParamBinding::ViewProjectionMatrix:
    case ShaderParamBinding::ModelMatrix:
    case ShaderParamBinding::ModelViewMatrix:
    case ShaderParamBinding::ModelViewProjectionMatrix:
        _type = ShaderValueType::Matrix4;
        break;
    }
}

ShaderParam::ShaderParam(const std::string& name, const ShaderValue& defaultValue) :
    _name(name),
    _type(defaultValue.type()),
    _binding(ShaderParamBinding::None),
    _defaultValueSet(true),
    _defaultValue(defaultValue),
    _location(-1)
{
}

ShaderValueType ShaderParam::type() const
{
    return _type;
}

ShaderParamBinding ShaderParam::binding() const
{
    return _binding;
}

bool ShaderParam::hasBinding() const
{
    return _binding != ShaderParamBinding::None;
}

const ShaderValue& ShaderParam::defaultValue() const
{
    return _defaultValue;
}

bool ShaderParam::hasDefaultValue() const
{
    return _defaultValueSet;
}

const std::string& ShaderParam::name() const
{
    return _name;
}

int ShaderParam::location() const
{
    return _location;
}

void ShaderParam::setLocation(int location)
{
    _location = location;
}
