#pragma once

namespace hect
{

///
/// A scene of entities.
class Scene :
    public Uncopyable
{
    friend class Entity;
public:

    ///
    /// Constructs a scene.
    Scene();

    ///
    /// Removes all entities from all systems.
    ~Scene();

    ///
    /// Refreshes entity membership of all systems.
    ///
    /// \remarks If an entity was created/activated since the last refresh then
    /// it will be added to each system based on its components.  If an entity
    /// was deactivated since the last refresh then it will be removed from all
    /// systems it was a member of.
    void refresh();

    ///
    /// Adds a system to the scene.
    ///
    /// \remarks Any entities that belong to the system based on their
    /// components will be added to the system.
    ///
    /// \param system The system.
    void addSystem(System& system);

    ///
    /// Removes a system from the scene.
    ///
    /// \remarks Any entities the systems has will be removed.
    ///
    /// \param system The system.
    void removeSystem(System& system);

    ///
    /// Creates a new entity.
    ///
    /// \returns The new entity.
    Entity createEntity();

    ///
    /// Creates a new entity copied from another.
    ///
    /// \param entity The entity to copy from.
    ///
    /// \returns The new entity.
    Entity copyEntity(Entity entity);

    ///
    /// Returns the entity with the given ID.
    Entity entityWithId(Entity::Id id);

    ///
    /// Returns the first entity with a specific component type.
    ///
    /// \returns The found entity; null if no entity with the component type
    /// was found.
    template <typename T>
    Entity entityWithComponent();

private:
    enum
    {
        InitialPoolSize = 128
    };

    void _destroyEntity(Entity& entity);

    void _activateEntity(Entity& entity);
    void _deactivateEntity(Entity& entity);

    bool _isActivated(const Entity& entity) const;
    bool _isNull(const Entity& entity) const;

    template <typename T>
    bool _hasComponent(const Entity& entity) const;

    template <typename T>
    T& _addComponent(Entity& entity, const BaseComponent::Ref& component);

    void _addComponentWithoutReturn(Entity& entity, const BaseComponent::Ref& component);

    template <typename T>
    void _removeComponent(Entity& entity);

    template <typename T>
    T& _component(const Entity& entity);

    size_t _entityCount;

    // The next entity ID to use when creating an entity (if the queue is
    // empty)
    Entity::Id _nextId;

    // A queue of entity IDs to use next when creating an entity
    std::queue<Entity::Id> _nextIds;

    // For each entity, the attributes it possesses
    std::vector<EntityAttributes> _deactivatedAttributes;

    // For each entity, the attributes it possesses
    std::vector<EntityAttributes> _attributes;

    // For each entity, its components mapped by type
    std::vector<std::map<ComponentTypeId, BaseComponent::Ref>> _components;

    // Entities deactivated since the last call to refresh()
    std::vector<Entity> _deactivatedEntities;

    // Entities activated since the last call to refresh()
    std::vector<Entity> _activatedEntities;

    // Entities destoryed since the last call to refresh()
    std::vector<Entity> _destroyedEntities;

    // Systems involved in the scene
    std::vector<System*> _systems;
};

}

#include "Scene.inl"