#include "Hect.h"

using namespace hect;

Material::Material()
{
}

Material::Material(const Technique::Array& techniques) :
    _techniques(techniques)
{
}

const Technique::Array& Material::techniques() const
{
    return _techniques;
}