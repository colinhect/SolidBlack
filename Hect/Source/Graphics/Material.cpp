#include "Hect.h"

using namespace hect;

Material::Material()
{
}

Material::Material(const std::string& name, const Technique::Array& techniques) :
    _name(name),
    _techniques(techniques)
{
}

const std::string& Material::name() const
{
    return _name;
}

const Technique::Array& Material::techniques() const
{
    return _techniques;
}