#pragma once

namespace hect
{

///
/// A scene filled with entities.
class Scene :
    public Uncopyable
{
    friend class Entity;
    friend class EntityFactory;
public:

    ///
    /// Constructs a scene with a entity pool size.
    ///
    /// \param entityPoolSize The size of the entity pool.
    Scene(size_t entityPoolSize);

    ///
    /// Removes all entities from all systems.
    virtual ~Scene();

    ///
    /// Adds/removes recently activated/deactivated entities to/from relevant
    /// systems and destroys entities pending destruction.
    void refresh();

    ///
    /// Adds a system to the scene.
    ///
    /// \param system The system.
    void addSystem(EntitySystem& system);

    ///
    /// Removes a system from the scene.
    ///
    /// \remarks Any entities the systems has will be removed.
    ///
    /// \param system The system.
    void removeSystem(EntitySystem& system);

    ///
    /// Creates a new entity.
    ///
    /// \returns The new entity.
    Entity createEntity();

private:
    void _activateEntity(const Entity& entity);
    void _destroyEntity(const Entity& entity);
    bool _isActivated(const Entity& entity) const;
    bool _isNull(const Entity& entity) const;

    template <typename T>
    bool _hasComponent(const Entity& entity) const;

    template <typename T>
    T& _addComponent(const Entity& entity, const std::shared_ptr<BaseComponent>& component);

    void _addComponentFromFactory(const Entity& entity, const std::shared_ptr<BaseComponent>& component);

    template <typename T>
    T& _component(const Entity& entity);

    // The next entity ID to use when creating an entity (if the queue is
    // empty)
    Entity::Id _nextId;

    // A queue of entity IDs to use next when creating an entity
    std::queue<Entity::Id> _nextIds;

    // For each entity, the attributes it possesses
    std::vector<EntityAttributes> _attributes;

    // For each entity, its components mapped by type
    std::vector<std::map<EntityComponentType, std::shared_ptr<BaseComponent>>> _components;

    // Entities activated since the last call to refresh()
    std::vector<Entity> _activatedEntities;

    // Entities destoryed since the last call to refresh()
    std::vector<Entity> _destroyedEntities;

    // Systems involved in the scene
    std::vector<EntitySystem*> _systems;
};

}

#include "Scene.inl"