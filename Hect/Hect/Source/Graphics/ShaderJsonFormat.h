namespace hect
{

///
/// Provides functionality for loading shaders from JSON.
class ShaderJsonFormat :
    public JsonFormat
{
public:

    ///
    /// Constucts a JSON format for shaders.
    ShaderJsonFormat();

    ///
    /// Loads a shader from a stream of JSON data.
    ///
    /// \param shader The shader to load to.
    /// \param dataValue The root data value of the JSON data.
    /// \param assetCache The asset cache to use to load referenced assets.
    void load(Shader& shader, const DataValue& dataValue, AssetCache& assetCache);

    ///
    /// Parses a shader value of a certain type.
    ///
    /// \param type The shader value type.
    /// \param dataValue The data value to parse from.
    ///
    /// \returns The parsed shader value.
    Shader::Value parseValue(Shader::Value::Type type, const DataValue& dataValue) const;

private:
    Shader::Parameter _parseParameter(const std::string& name, const DataValue& dataValue);
    Shader::Parameter::Binding _parseParameterBinding(const DataValue& dataValue);
    Shader::Value::Type _parseValueType(const DataValue& dataValue);

    std::map<std::string, Shader::Parameter::Binding> _parameterBindings;
    std::map<std::string, Shader::Value::Type> _valueTypes;
};

}