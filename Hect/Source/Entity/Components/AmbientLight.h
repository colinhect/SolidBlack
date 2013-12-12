#pragma once

namespace hect
{

///
/// An ambient light component
class AmbientLight :
    public Component<AmbientLight>
{
public:
    AmbientLight();

    ///
    /// Returns the color
    const Vector3<>& color() const;

    ///
    /// Sets the color.
    ///
    /// \param color The new color.
    void setColor(const Vector3<>& color);

private:
    Vector3<> _color;
};

///
/// Serializer for AmbientLight.
class AmbientLightSerializer :
    public ComponentSerializer<AmbientLight>
{
public:

    ///
    /// See BaseComponentSerializer::save()
    void save(const AmbientLight& light, DataWriter& writer) const;

    ///
    /// See BaseComponentSerializer::load()
    void load(AmbientLight& light, DataReader& reader, AssetCache& assetCache) const;
};

}