#pragma once

namespace hect
{

///
/// A game object in the scene.
///
/// \remarks An entity is in one of two states; activated or deactivated.  On
/// creation an entity is deactivated.  Components can only be added/removed 
/// when the entity is deactivated.
class Entity
{
    friend class Scene;
public:

    ///
    /// The ID of an entity within the pool of the scene.
    typedef uint32_t Id;

    ///
    /// Constructs a null entity.
    Entity();

    ///
    /// Returns the scene.
    Scene& scene();
    
    ///
    /// Enqueues the entity to be added to relevant systems on the next
    /// call to Scene::refresh().
    ///
    /// \remarks Once the entity is activated, components can no longer be
    /// added or removed.
    ///
    /// \throws Error If the entity is already activated (debug builds only).
    void activate();

    ///
    /// Enqueues the entity to be removed from relevant systems on the next
    /// call to Scene::refresh().
    ///
    /// \remarks Once the entity is deactivated, components can be added or
    /// removed.
    ///
    /// \throws Error If the entity is already deactivated (debug builds only).
    void deactivate();

    ///
    /// Enqueues the entity to be removed from relevant systems on the next
    /// call to Scene::refresh().
    void destroy();

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
    /// Adds a new component of a certain type to the entity.
    ///
    /// \param a0 The first argument in the constructor of the component.
    ///
    /// \returns The new component.
    ///
    /// \throws Error If the entity is activated or already has a component of
    /// the type (debug builds only).
    template <typename T, typename A0>
    T& addComponent(A0&& a0);

    ///
    /// Adds a new component of a certain type to the entity.
    ///
    /// \param a0 The first argument in the constructor of the component.
    /// \param a1 The second argument in the constructor of the component.
    ///
    /// \returns The new component.
    ///
    /// \throws Error If the entity is activated or already has a component of
    /// the type (debug builds only).
    template <typename T, typename A0, typename A1>
    T& addComponent(A0&& a0, A1&& a1);

    ///
    /// Adds a new component of a certain type to the entity.
    ///
    /// \param a0 The first argument in the constructor of the component.
    /// \param a1 The second argument in the constructor of the component.
    /// \param a2 The third argument in the constructor of the component.
    ///
    /// \returns The new component.
    ///
    /// \throws Error If the entity is activated or already has a component of
    /// the type (debug builds only).
    template <typename T, typename A0, typename A1, typename A2>
    T& addComponent(A0&& a0, A1&& a1, A2&& a2);

    ///
    /// Adds a new component of a certain type to the entity.
    ///
    /// \param a0 The first argument in the constructor of the component.
    /// \param a1 The second argument in the constructor of the component.
    /// \param a2 The third argument in the constructor of the component.
    /// \param a3 The fourth argument in the constructor of the component.
    ///
    /// \returns The new component.
    ///
    /// \throws Error If the entity is activated or already has a component of
    /// the type (debug builds only).
    template <typename T, typename A0, typename A1, typename A2, typename A3>
    T& addComponent(A0&& a0, A1&& a1, A2&& a2, A3&& a3);

    ///
    /// Adds a new component of a certain type to the entity.
    ///
    /// \param a0 The first argument in the constructor of the component.
    /// \param a1 The second argument in the constructor of the component.
    /// \param a2 The third argument in the constructor of the component.
    /// \param a3 The fourth argument in the constructor of the component.
    /// \param a4 The fifth argument in the constructor of the component.
    ///
    /// \returns The new component.
    ///
    /// \throws Error If the entity is activated or already has a component of
    /// the type (debug builds only).
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
    T& addComponent(A0&& a0, A1&& a1, A2&& a2, A3&& a3, A4&& a4);

    ///
    /// Returns the component of a certain type from an entity.
    ///
    /// \throws Error If the entity does not have a component of the type
    /// (debug builds only).
    template <typename T>
    T& component();

    ///
    /// Returns whether the entity is the same as another.
    bool operator==(const Entity& entity) const;

private:
    Entity(Scene& scene, Id id);

    Scene* _scene;
    Id _id;
};

}

#include "Entity.inl"