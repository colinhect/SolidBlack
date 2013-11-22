#include "Hect.h"

using namespace hect;

Uniform::Uniform(const std::string& name, UniformType type) :
    _name(name),
    _type(type),
    _binding(UniformBinding::None),
    _defaultValueSet(false),
    _location(-1)
{
}

Uniform::Uniform(const std::string& name, UniformBinding binding) :
    _name(name),
    _type(UniformType::Float),
    _binding(binding),
    _defaultValueSet(false),
    _location(-1)
{
    switch (binding)
    {
    case UniformBinding::RenderTargetSize:
        _type = UniformType::Vector2;
        break;
    case UniformBinding::CameraPosition:
    case UniformBinding::CameraUp:
        _type = UniformType::Vector3;
        break;
    case UniformBinding::ViewMatrix:
    case UniformBinding::ProjectionMatrix:
    case UniformBinding::ViewProjectionMatrix:
    case UniformBinding::ModelMatrix:
    case UniformBinding::ModelViewMatrix:
    case UniformBinding::ModelViewProjectionMatrix:
        _type = UniformType::Matrix4;
        break;
    }
}

Uniform::Uniform(const std::string& name, const UniformValue& defaultValue) :
    _name(name),
    _type(defaultValue.type()),
    _binding(UniformBinding::None),
    _defaultValueSet(true),
    _defaultValue(defaultValue),
    _location(-1)
{
}

UniformType Uniform::type() const
{
    return _type;
}

UniformBinding Uniform::binding() const
{
    return _binding;
}

bool Uniform::hasBinding() const
{
    return _binding != UniformBinding::None;
}

const UniformValue& Uniform::defaultValue() const
{
    return _defaultValue;
}

bool Uniform::hasDefaultValue() const
{
    return _defaultValueSet;
}

const std::string& Uniform::name() const
{
    return _name;
}

int Uniform::location() const
{
    return _location;
}

void Uniform::setLocation(int location)
{
    _location = location;
}
