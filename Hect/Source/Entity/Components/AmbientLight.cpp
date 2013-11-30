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

void AmbientLightSerializer::deserialize(AmbientLight& light, const DataValue& dataValue, AssetCache& assetCache) const
{
    // Color
    const DataValue& color = dataValue["color"];
    if (color.isArray())
    {
        light.setColor(color.asVector3());
    }
}