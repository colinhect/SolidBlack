#pragma once

namespace hect
{

///
/// Provides functionality for loading input axes from data values.
class InputAxisDataValueFormat
{
public:

    ///
    /// Loads an input axis from a data value.
    ///
    /// \param name The name of the axis.
    /// \param dataValue The data value to load the input axis from.
    ///
    /// \returns The input axis.
    ///
    /// \throws Error If an error occurred while loading the axis.
    static InputAxis load(const std::string& name, const DataValue& dataValue);

private:
    static InputAxisSource _parseSource(const DataValue& dataValue);
    static Key _parseKey(const DataValue& dataValue);
    static MouseButton _parseMouseButton(const DataValue& dataValue);
};

}