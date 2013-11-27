#pragma once

namespace hect
{

///
/// Provides functionality for loading shaders from data values.
class ShaderDataFormat
{
public:

    ///
    /// Loads a shader from a data value.
    ///
    /// \param shader The shader to load to.
    /// \param dataValue The root data value.
    /// \param assetCache The asset cache to use to load referenced assets.
    static void load(Shader& shader, const DataValue& dataValue, AssetCache& assetCache);

    ///
    /// Parses a uniform value of a certain type.
    ///
    /// \param type The uniform value type.
    /// \param dataValue The data value to parse from.
    ///
    /// \returns The parsed uniform value.
    static UniformValue parseValue(UniformType type, const DataValue& dataValue);

private:
    static Uniform _parseUniform(const std::string& name, const DataValue& dataValue);
    static UniformBinding _parseUniformBinding(const DataValue& dataValue);
    static UniformType _parseType(const DataValue& dataValue);
};

}