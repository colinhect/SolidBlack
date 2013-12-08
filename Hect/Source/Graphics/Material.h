#pragma once

namespace hect
{

///
/// The manner in which a surface is rendered.
class Material
{
public:

    ///
    /// A shared reference to a material.
    typedef std::shared_ptr<Material> Ref;

    ///
    /// An array of shared material references.
    typedef std::vector<Material::Ref> RefArray;

    ///
    /// Constructs a material without any techniques.
    Material();

    ///
    /// Constructs a material given its techniques.
    ///
    /// \param name The name of the material.
    /// \param techniques The techniques to include in the material.
    Material(const std::string& name, const Technique::Array& techniques);

    ///
    /// Returns the name.
    const std::string& name() const;

    ///
    /// Returns the techniques.
    const Technique::Array& techniques() const;

private:
    std::string _name;
    Technique::Array _techniques;
};

}