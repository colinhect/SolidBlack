#pragma once

namespace hect
{

///
/// Contains entity state information and component existence.
class EntityData
{
public:

    ///
    /// Returns whether the entity is activated.
    bool isActivated() const;

    ///
    /// Sets whether the entity is activated.
    ///
    /// \param activated The new activated value.
    void setActivated(bool activated);

    ///
    /// Returns whether the entity is destroyed.
    bool isDestroyed() const;

    ///
    /// Sets whether the entity is destroyed.
    ///
    /// \param destroyed The new destroyed value.
    void setDestroyed(bool destroyed);

    ///
    /// Returns whether the entity is null.
    bool isNull() const;

    ///
    /// Sets whether the entity is null.
    ///
    /// \param null The new null value.
    void setNull(bool null);

    ///
    /// Returns whether the entity as a component of a certain type.
    ///
    /// \param typeId The component type id.
    bool hasComponent(ComponentTypeId typeId) const;

    ///
    /// Sets whether the entity as a component of a certain type.
    ///
    /// \param typeId The component type id.
    /// \param value Whether the entity has the component.
    void setHasComponent(ComponentTypeId typeId, bool value);

private:
    std::bitset<64> _bitset;
};

}