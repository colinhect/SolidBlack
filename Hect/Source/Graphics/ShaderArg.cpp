#include "Hect.h"

using namespace hect;

ShaderArg::ShaderArg(const std::string& paramName, const ShaderValue& value) :
    _paramName(paramName),
    _value(value)
{
}

const std::string& ShaderArg::paramName() const
{
    return _paramName;
}

const ShaderValue& ShaderArg::value() const
{
    return _value;
}