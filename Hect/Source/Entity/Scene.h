#pragma once

namespace hect
{

///
/// A scene of entities.
class Scene :
    public Uncopyable
{
    friend class Entity;
    friend class EntitySerializer;
public:

    ///
    /// Constructs a scene with no entities.
    Scene();

    ///
    /// Removes all entities from all systems.
    ~Scene();

    ///
    /// All entities activated since the last call to refresh() are added to
    /// the systems that include them.  All entities destroyed since the last
    /// call to refresh are removed from the systems that include them.
    void refresh();

    ///
    /// Adds a system to the scene.
    ///
    /// \remarks All activated entities that are included in the system are
    /// added to the system.
    ///
    /// \param system The system to add.
    void addSystem(System& system);

    ///
    /// Removes a system from the scene.
    ///
    /// \remarks All entities included in the system are removed from the
    /// system.
    ///
    /// \param system The system to remove.
    void removeSystem(System& system);

    ///
    /// Creates a new entity.
    ///
    /// \returns The new entity.
    Entity createEntity();

private:
    enum
    {
        InitialPoolSize = 128
    };

    Entity _entityWithId(Entity::Id id);

    Entity _cloneEntity(Entity entity);

    void _destroyEntity(Entity& entity);
    void _activateEntity(Entity& entity);

    bool _isActivated(const Entity& entity) const;
    bool _isNull(const Entity& entity) const;

    template <typename T>
    bool _hasComponent(const Entity& entity) const;

    template <typename T>
    T& _addComponent(Entity& entity, const BaseComponent::Ref& component);
    void _addComponentWithoutReturn(Entity& entity, const BaseComponent::Ref& component);

    template <typename T>
    T& _component(const Entity& entity);

    // The number of entities (includes non-activated and activated entities)
    size_t _entityCount;

    // The next entity id to use when creating an entity (if the queue is
    // empty)
    Entity::Id _nextEntityId;

    // A queue of entity IDs to use next when creating an entity
    std::queue<Entity::Id> _nextEntityIds;

    // Data for each entity
    std::vector<EntityData> _entityData;

    // Components for each entity
    std::vector<std::map<ComponentTypeId, BaseComponent::Ref>> _entityComponents;

    // Entities activated since the last call to refresh()
    std::vector<Entity::Id> _activatedEntityIds;

    // Entities destroyed since the last call to refresh()
    std::vector<Entity::Id> _destroyedEntityIds;

    // Systems involved in the scene
    std::vector<System*> _systems;
};

}

#include "Scene.inl"