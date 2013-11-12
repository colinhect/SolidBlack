namespace hect
{

///
/// Provides functionality for loading materials from JSON.
class MaterialJsonFormat :
    public JsonFormat
{
public:

    ///
    /// Constucts a JSON format for materials.
    MaterialJsonFormat();

    ///
    /// Loads a material from a stream of JSON data.
    ///
    /// \param material The material to load to.
    /// \param stream The stream containing the JSON data.
    /// \param assetCache The asset cache to use to load referenced assets.
    void load(Material& material, ReadStream& stream, AssetCache& assetCache);

private:
    RenderMode::State _parseState(const DataValue& dataValue);
    RenderMode::BlendFactor _parseBlendFactor(const DataValue& dataValue);

    std::map<std::string, RenderMode::State> _states;
    std::map<std::string, RenderMode::BlendFactor> _blendFactors;
};

}