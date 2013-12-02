#pragma once

namespace hect
{

///
/// A game object in a scene.
class Entity
{
    friend class BaseComponent;
    friend class Scene;
public:

    ///
    /// The id of an entity within a scene.
    typedef uint32_t Id;

    ///
    /// Constructs a null entity.
    ///
    /// \throws Error If the entity is not in a scene.
    Entity();

    ///
    /// Returns the scene.
    Scene& scene();

    ///
    /// Returns the id.
    Id id() const;

    ///
    /// Enqueues the entity to be added to relevant systems on the next
    /// call to Scene::refresh().
    ///
    /// \remarks Once the entity is activated, components can no longer be
    /// added or removed.  The entity cannot be deactivated.
    ///
    /// \throws Error If the entity is already activated or is null (debug
    /// builds only).
    void activate();

    ///
    /// Enqueues the entity to be removed from relevant systems on the next
    /// call to Scene::refresh().
    ///
    /// \throws Error If the entity is already destroyed or is null (debug
    /// builds only).
    void destroy();

    ///
    /// Creates a clone of the entity.
    Entity clone() const;

    ///
    /// Returns whether the entity is activated.
    bool isActivated() const;

    ///
    /// Returns whether the entity is null.
    bool isNull() const;

    ///
    /// Returns whether an entity has a component of a certain type.
    ///
    /// \warning Always call this before component().  It is very fast to
    /// check if an entity has a component.
    ///
    /// \throws Error If the entity is null (debug builds only).
    template <typename T>
    bool hasComponent() const;

    ///
    /// Adds a new component of a certain type to the entity.
    ///
    /// \returns The new component.
    ///
    /// \throws Error If the entity is activated or already has a component of
    /// the type (debug builds only).
    template <typename T>
    T& addComponent();

    ///
    /// Adds a new component to the entity.
    ///
    /// \param component The new component (the entity will take ownership of
    /// the components lifetime.
    ///
    /// \throws Error If the entity is activated or already has a component of
    /// the type (debug builds only).
    void addComponent(BaseComponent* component);

    ///
    /// Returns the component of a certain type from an entity.
    ///
    /// \warning Always call hasComponent() before this.  It is very fast to
    /// check if an entity has a component.
    ///
    /// \throws Error If the entity does not have a component of the type
    /// (debug builds only).
    template <typename T>
    T& component();

    ///
    /// Returns true if the entity is not null; false otherwise.
    operator bool() const;

    bool operator==(const Entity& entity) const;
    bool operator!=(const Entity& entity) const;

private:
    Entity(Scene& scene, Id id);

    Scene* _scene;
    Id _id;
};

}

#include "Entity.inl"