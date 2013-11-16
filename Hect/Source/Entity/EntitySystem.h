#pragma once

namespace hect
{

///
/// A system which handles entities which have specific components.
class EntitySystem
{
public:

    ///
    /// A shared reference to an entity system.
    typedef std::shared_ptr<EntitySystem> Ref;

    ///
    /// Construct an entity system without an update priority.
    EntitySystem();

    ///
    /// Adds an entity to the system.
    ///
    /// \param entity The entity.
    void addEntity(Entity& entity);

    ///
    /// Removes an entity from the system.
    ///
    /// \param entity The entity.
    void removeEntity(Entity& entity);

    ///
    /// Removes all from the system.
    void removeAllEntities();

    ///
    /// Returns the required entity attributes to be added to this system.
    const EntityAttributes& requiredAttributes() const;

protected:

    ///
    /// Called when an entity is added to the system.
    ///
    /// \param entity The entity.
    virtual void onAddEntity(Entity& entity);

    ///
    /// Called when an entity is removed from the system.
    ///
    /// \param entity The entity.
    virtual void onRemoveEntity(Entity& entity);

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

#include "EntitySystem.inl"