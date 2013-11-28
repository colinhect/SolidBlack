#pragma once

namespace hect
{

///
/// A directional light component
class DirectionalLight :
    public Renderable
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

    ///
    /// \copydoc Renderable::render()
    void render(const Camera& camera, RenderingSystem& renderingSystem);

private:
    Vector3<> _direction;
    Vector3<> _color;
};

class DirectionalLightSerializer :
    public ComponentSerializer<DirectionalLight>
{
public:
    void deserialize(DirectionalLight& light, const DataValue& dataValue, AssetCache& assetCache) const;
};

}