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
    virtual void addEntity(const Entity& entity);

    ///
    /// Removes an entity from the system.
    ///
    /// \param entity The entity.
    virtual void removeEntity(const Entity& entity);

    ///
    /// Removes all from the system.
    void removeAllEntities();

    ///
    /// Returns whether the system includes the given entity.
    ///
    /// \remarks If this returns false for an entity, then addEntity() will
    /// not even be called for that entity.
    ///
    /// \param entity The entity to check if the system includes.
    virtual bool includesEntity(const Entity& entity) const;

    ///
    /// Returns the entities currently in the system.
    std::vector<Entity>& entities();

    ///
    /// Returns the entities currently in the system.
    const std::vector<Entity>& entities() const;

private:
    std::vector<Entity> _entities;
};

}