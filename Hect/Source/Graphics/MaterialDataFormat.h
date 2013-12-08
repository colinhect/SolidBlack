#pragma once

namespace hect
{

///
/// Provides functionality for loading materials from data values.
class MaterialDataFormat
{
public:

    ///
    /// Loads a material from a data value.
    ///
    /// \param material The material to load to.
    /// \param name The name of the material.
    /// \param dataValue The root data value.
    /// \param assetCache The asset cache to use to load referenced assets.
    static void load(Material& material, const std::string& name, const DataValue& dataValue, AssetCache& assetCache);

private:
    static RenderState _parseState(const DataValue& dataValue);
    static BlendFactor _parseBlendFactor(const DataValue& dataValue);
};

}