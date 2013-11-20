#pragma once

namespace hect
{

///
/// A value for a parameter.
class ShaderArg
{
public:

    ///
    /// An array of arguments.
    typedef std::vector<ShaderArg> Array;

    ///
    /// Constructs an argument given a name an a value.
    ///
    /// \param paramName The name of the parameter.
    /// \param value The default value.
    ShaderArg(const std::string& paramName, const ShaderValue& value);

    ///
    /// Returns the name of the parameter.
    const std::string& paramName() const;

    ///
    /// Returns the value.
    const ShaderValue& value() const;

private:
    std::string _paramName;
    ShaderValue _value;
};

}