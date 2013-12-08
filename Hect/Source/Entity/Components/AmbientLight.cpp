#include "Hect.h"

using namespace hect;

AmbientLight::AmbientLight() :
    _color(Vector3<>::one())
{
}

const Vector3<>& AmbientLight::color() const
{
    return _color;
}

void AmbientLight::setColor(const Vector3<>& color)
{
    _color = color;
}

void AmbientLightSerializer::save(const AmbientLight& light, ComponentWriter& writer) const
{
    writer.writeMemberVector3("color", light.color());
}

void AmbientLightSerializer::load(AmbientLight& light, ComponentReader& reader, AssetCache& assetCache) const
{
    assetCache;

    if (reader.hasMember("color"))
    {
        light.setColor(reader.readMemberVector3("color"));
    }
}