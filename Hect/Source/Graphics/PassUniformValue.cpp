#include "Hect.h"

using namespace hect;

PassUniformValue::PassUniformValue(const std::string& uniformName, const UniformValue& value) :
    _uniformName(uniformName),
    _value(value)
{
}

const std::string& PassUniformValue::uniformName() const
{
    return _uniformName;
}

const UniformValue& PassUniformValue::value() const
{
    return _value;
}