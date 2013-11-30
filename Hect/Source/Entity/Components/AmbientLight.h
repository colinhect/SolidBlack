#pragma once

namespace hect
{

///
/// An ambient light component
class AmbientLight :
    public Renderable
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

    ///
    /// \copydoc Renderable::render()
    void render(const Camera& camera, RenderingSystem& renderingSystem);

private:
    Vector3<> _color;
};

class AmbientLightSerializer :
    public ComponentSerializer<AmbientLight>
{
public:
    void deserialize(AmbientLight& light, const DataValue& dataValue, AssetCache& assetCache) const;
};

}