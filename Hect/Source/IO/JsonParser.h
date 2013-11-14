namespace hect
{

///
/// Provides the functionality for parsing JSON into a data value.
class JsonParser
{
public:

    ///
    /// Parses a JSON string into a data value.
    ///
    /// \param json The JSON string.
    ///
    /// \returns The resulting data value.
    DataValue parse(const std::string& json);

    ///
    /// Parses a stream containing JSON text into a data value.
    ///
    /// \param stream The stream containing JSON text.
    ///
    /// \returns The resulting data value.
    DataValue parse(ReadStream& stream);
};

}