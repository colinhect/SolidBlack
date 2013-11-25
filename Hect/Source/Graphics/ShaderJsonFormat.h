#pragma once

namespace hect
{

///
/// Provides functionality for loading shaders from JSON.
class ShaderJsonFormat
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
    /// Parses a uniform value of a certain type.
    ///
    /// \param type The uniform value type.
    /// \param dataValue The data value to parse from.
    ///
    /// \returns The parsed uniform value.
    UniformValue parseValue(UniformType type, const DataValue& dataValue) const;

private:
    Uniform _parseUniform(const std::string& name, const DataValue& dataValue);
    UniformBinding _parseUniformBinding(const DataValue& dataValue);
    UniformType _parseType(const DataValue& dataValue);

    std::map<std::string, UniformBinding> _uniformBindings;
    std::map<std::string, UniformType> _valueTypes;
};

}