#pragma once

namespace hect
{

/// \cond INTERNAL

enum class EntityAttribute
{
    MarkedForDestruction = 59,
    MarkedForActivation = 60,
    MarkedForDeactivation = 61,
    Activated = 62,
    Exists = 63
};

/// \endcond

///
/// Contains metadata for an entity.
class EntityAttributes
{
public:

    ///
    /// Returns whether it has the given attribute.
    //
    /// \param attribute The attribute.
    bool hasAttribute(EntityAttribute attribute) const;

    ///
    /// Sets the value of a specific attribute.
    //
    /// \param attribute The attribute.
    /// \param value The new value.
    void setAttribute(EntityAttribute attribute, bool value);

    ///
    /// Returns whether the entity has a component of a certain type.
    ///
    /// \param type The component type.
    bool hasComponent(ComponentTypeId type) const;

    ///
    /// Sets whether the entity as a component of a certain type.
    ///
    /// \param type The component type.
    /// \param value True if the entity has the component; false otherwise.
    void setHasComponent(ComponentTypeId type, bool value);

    ///
    /// Returns whether these attributes have all of the given attributes.
    ///
    /// \param attributes The attributes.
    bool contains(const EntityAttributes& attributes) const;

    ///
    /// Returns the attributes which are different than the given attributes.
    ///
    /// \param attributes The attributes.
    ///
    /// \returns The differing attributes.
    EntityAttributes difference(const EntityAttributes& attributes) const;

private:
    std::bitset<64> _bitset;
};

}