#include "Hect.h"

using namespace hect;

DirectionalLight::DirectionalLight() :
    _direction(Vector3<>::unitX()),
    _color(Vector3<>::one())
{
}

const Vector3<>& DirectionalLight::direction() const
{
    return _direction;
}

void DirectionalLight::setDirection(const Vector3<>& direction)
{
    _direction = direction;
}

const Vector3<>& DirectionalLight::color() const
{
    return _color;
}

void DirectionalLight::setColor(const Vector3<>& color)
{
    _color = color;
}

void DirectionalLight::render(const Camera& camera, RenderingSystem& renderingSystem)
{
    renderingSystem.addDirectionalLight(*this);
}

void DirectionalLightSerializer::deserialize(DirectionalLight& light, const DataValue& dataValue, AssetCache& assetCache) const
{
    // Direction
    const DataValue& direction = dataValue["direction"];
    if (direction.isArray())
    {
        light.setDirection(direction.asVector3());
    }

    // Color
    const DataValue& color = dataValue["color"];
    if (color.isArray())
    {
        light.setColor(color.asVector3());
    }
}