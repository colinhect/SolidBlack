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
    _direction = direction.normalized();
}

const Vector3<>& DirectionalLight::color() const
{
    return _color;
}

void DirectionalLight::setColor(const Vector3<>& color)
{
    _color = color;
}

void DirectionalLightSerializer::save(const DirectionalLight& light, ComponentWriter& writer) const
{
    writer.writeMemberVector3("direction", light.direction());
    writer.writeMemberVector3("color", light.color());
}

void DirectionalLightSerializer::load(DirectionalLight& light, ComponentReader& reader, AssetCache& assetCache) const
{
    assetCache;

    if (reader.hasMember("direction"))
    {
        light.setDirection(reader.readMemberVector3("direction"));
    }

    if (reader.hasMember("color"))
    {
        light.setColor(reader.readMemberVector3("color"));
    }
}