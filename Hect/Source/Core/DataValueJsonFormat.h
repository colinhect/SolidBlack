#pragma once

namespace hect
{

///
/// Provides the functionality for parsing JSON into a data value.
class DataValueJsonFormat
{
public:

    ///
    /// Saves a data value to a JSON string.
    ///
    /// \param dataValue The data value.
    /// \param json The resulting JSON string.
    static void save(const DataValue& dataValue, std::string& json);

    ///
    /// Saves a data value to a stream as a JSON string.
    ///
    /// \param dataValue The data value.
    /// \param stream The stream to write to.
    static void save(const DataValue& dataValue, WriteStream& stream);

    ///
    /// Parses a JSON string into a data value.
    ///
    /// \param dataValue The data value to load to.
    /// \param json The JSON string.
    static void load(DataValue& dataValue, const std::string& json);

    ///
    /// Parses JSON from a stream into a data value.
    ///
    /// \param dataValue The data value to load to.
    /// \param stream The stream to read from.
    static void load(DataValue& dataValue, ReadStream& stream);
};

}