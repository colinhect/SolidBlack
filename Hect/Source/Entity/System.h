#pragma once

namespace hect
{

///
/// A system which handles entities with specific components.
class System
{
public:

    ///
    /// Adds an entity to the system.
    ///
    /// \param entity The entity.
    virtual void addEntity(Entity& entity);

    ///
    /// Removes an entity from the system.
    ///
    /// \param entity The entity.
    virtual void removeEntity(Entity& entity);

    ///
    /// Removes all from the system.
    void removeAllEntities();

    ///
    /// Returns the required entity attributes to be added to this system.
    const EntityAttributes& requiredAttributes() const;

protected:

    ///
    /// Returns the entities currently in the system.
    std::vector<Entity>& entities();

    ///
    /// Returns the entities currently in the system.
    const std::vector<Entity>& entities() const;

    ///
    /// Adds a component requirement for entities in this system.
    template <typename T>
    void requireComponent();

private:
    std::vector<Entity> _entities;
    EntityAttributes _requiredAttributes;
};

}

#include "System.inl"
