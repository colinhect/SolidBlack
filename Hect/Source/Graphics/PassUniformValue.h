#pragma once

namespace hect
{

///
/// A pass's value for a uniform.
class PassUniformValue
{
public:

    ///
    /// An array of pass uniform values.
    typedef std::vector<PassUniformValue> Array;

    ///
    /// Constructs an pass uniform value given a name an a value.
    ///
    /// \param uniformName The name of the uniform.
    /// \param value The default value.
    PassUniformValue(const std::string& uniformName, const UniformValue& value);

    ///
    /// Returns the name of the uniform.
    const std::string& uniformName() const;

    ///
    /// Returns the value.
    const UniformValue& value() const;

private:
    std::string _uniformName;
    UniformValue _value;
};

}