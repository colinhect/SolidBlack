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
    /// Constructs a scene with no entities.
    Scene();

    ///
    /// Removes all entities from all systems.
    ~Scene();

    ///
    /// Refreshes the scene.
    ///
    /// \remarks All entities activated since the last call to refresh() are
    /// added to the systems that include them.  All entities destroyed since
    /// the last call to refresh are removed from the systems that include
    /// them.
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
    /// Creates a new entity using the next available id.
    ///
    /// \returns The new entity.
    Entity createEntity();

    ///
    /// Returns the entity of the given id.
    Entity entityWithId(Entity::Id id) const;

    ///
    /// Serializes all activated entities in the scene to a data value.
    ///
    /// \param dataValue The data value.
    void save(DataValue& dataValue) const;

    ///
    /// Serializes all activated entities in the scene to a binary stream.
    ///
    /// \param stream The stream to write to.
    void save(WriteStream& stream) const;

    ///
    /// Deserializes all entities from a data value and activates them in the
    /// scene.
    ///
    /// \param dataValue The data value.
    /// \param assetCache The asset cache to use to load referenced assets.
    void load(const DataValue& dataValue, AssetCache& assetCache);

    ///
    /// Deserializes all entities from a binary stream and activates them in
    /// the scene.
    ///
    /// \param stream The stream to read from.
    /// \param assetCache The asset cache to use to load referenced assets.
    void load(ReadStream& stream, AssetCache& assetCache);
    
    ///
    /// Returns the entity serializer;
    EntitySerializer& entitySerializer();

private:
    enum
    {
        InitialPoolSize = 128
    };

    Entity _cloneEntity(const Entity& entity);

    void _destroyEntity(const Entity& entity);
    void _activateEntity(const Entity& entity);

    bool _isActivated(const Entity& entity) const;
    bool _isNull(const Entity& entity) const;

    bool _isSerializable(const Entity& entity) const;
    void _setSerializable(const Entity& entity, bool serializable);

    template <typename T>
    bool _hasComponent(const Entity& entity) const;

    template <typename T>
    T& _addComponent(const Entity& entity, const BaseComponent::Ref& component);
    void _addComponentWithoutReturn(const Entity& entity, const BaseComponent::Ref& component);

    template <typename T>
    T& _component(const Entity& entity);

    // The number of activated entities
    size_t _activatedEntityCount;

    // The entity id pool
    IdPool<Entity::Id> _entityIdPool;

    // Data for each entity
    std::vector<EntityData> _entityData;

    // Components for each entity
    std::vector<std::map<ComponentTypeId, BaseComponent::Ref>> _entityComponents;

    // Entities activated since the last call to refresh()
    std::vector<Entity::Id> _activatedEntities;

    // Entities destroyed since the last call to refresh()
    std::vector<Entity::Id> _destroyedEntities;

    // Systems involved in the scene
    std::vector<System*> _systems;

    // The entity serializer
    EntitySerializer _entitySerializer;
};

}

#include "Scene.inl"