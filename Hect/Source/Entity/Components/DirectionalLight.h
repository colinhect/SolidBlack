#pragma once

namespace hect
{

///
/// A directional light component
class DirectionalLight :
    public Component<DirectionalLight>
{
public:

    ///
    /// Constructs a directional light.
    DirectionalLight();

    ///
    /// Returns the world-space direction.
    const Vector3<>& direction() const;

    ///
    /// Sets the world-space direction.
    ///
    /// \param direction The new world-space direction.
    void setDirection(const Vector3<>& direction);

    ///
    /// Returns the color
    const Vector3<>& color() const;

    ///
    /// Sets the color.
    ///
    /// \param color The new color.
    void setColor(const Vector3<>& color);

private:
    Vector3<> _direction;
    Vector3<> _color;
};

class DirectionalLightSerializer :
    public ComponentSerializer<DirectionalLight>
{
public:
    void serialize(const DirectionalLight& light, DataValue& dataValue) const;
    void deserialize(DirectionalLight& light, const DataValue& dataValue, AssetCache& assetCache) const;
};

}