#pragma once

namespace hect
{

///
/// An ambient light component
class AmbientLight :
    public Component<AmbientLight>
{
public:

    ///
    /// Constructs an ambient light.
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

class AmbientLightSerializer :
    public ComponentSerializer<AmbientLight>
{
public:
    void save(const AmbientLight& light, WriteStream& stream) const;
    void load(AmbientLight& light, ReadStream& stream, AssetCache& assetCache) const;

    void load(AmbientLight& light, const DataValue& dataValue, AssetCache& assetCache) const;
};

}