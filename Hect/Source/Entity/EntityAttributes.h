#pragma once

namespace hect
{

///
/// Contains metadata for an entity.
class EntityAttributes
{
public:

    ///
    /// Returns whether the entity is null.
    bool isNull() const;

    ///
    /// Sets whether the entity is null.
    ///
    /// \param value True if the null is activated; false otherwise.
    void setNull(bool value);

    ///
    /// Returns whether the entity is activated.
    bool isActivated() const;

    ///
    /// Sets whether the entity is activated.
    ///
    /// \param value True if the entity is activated; false otherwise.
    void setActivated(bool value);

    ///
    /// Returns whether the entity has a component of a certain type.
    ///
    /// \param type The component type.
    bool hasComponent(ComponentType type) const;

    ///
    /// Sets whether the entity as a component of a certain type.
    ///
    /// \param type The component type.
    /// \param value True if the entity has the component; false otherwise.
    void setHasComponent(ComponentType type, bool value);

    ///
    /// Returns whether these attributes have all of the given attributes.
    ///
    /// \param attributes The attributes.
    bool contains(const EntityAttributes& attributes) const;

private:
    std::bitset<64> _bitset;
};

}