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

void DirectionalLightSerializer::save(const DirectionalLight& light, WriteStream& stream) const
{
    stream.writeVector3(light.direction());
    stream.writeVector3(light.color());
}

void DirectionalLightSerializer::load(DirectionalLight& light, ReadStream& stream, AssetCache& assetCache) const
{
    light.setDirection(stream.readVector3());
    light.setColor(stream.readVector3());
}

void DirectionalLightSerializer::load(DirectionalLight& light, const DataValue& dataValue, AssetCache& assetCache) const
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