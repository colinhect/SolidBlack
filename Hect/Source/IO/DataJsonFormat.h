#pragma once

namespace hect
{

///
/// Provides the functionality for parsing JSON into a data value.
class DataJsonFormat
{
public:

    ///
    /// Parses a JSON string into a data value.
    ///
    /// \param json The JSON string.
    ///
    /// \returns The resulting data value.
    static DataValue load(const std::string& json);

    ///
    /// Parses a stream containing JSON text into a data value.
    ///
    /// \param stream The stream containing JSON text.
    ///
    /// \returns The resulting data value.
    static DataValue load(ReadStream& stream);
};

}