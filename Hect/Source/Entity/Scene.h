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
    ///
    /// \remarks Entity components often need access to engine which is why the
    /// scene is given the engine.
    ///
    /// \param engine The engine.
    Scene(Engine& engine);

    ///
    /// Constructs a scene given an asset cache.
    ///
    /// \remarks Entity components often need access to engine which is why the
    /// scene is given the engine.
    ///
    /// \param engine The engine.
    /// \param assetCache An asset cache.
    Scene(Engine& engine, AssetCache& assetCache);

    ///
    /// Removes all entities from all systems.
    ~Scene();

    ///
    /// Adds/removes recently activated/deactivated entities to/from relevant
    /// systems and destroys entities pending destruction.
    void refresh();

    ///
    /// Returns the engine.
    Engine& engine();

    ///
    /// Adds a system to the scene.
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
    /// Creates a new entity from an asset.
    ///
    /// \param path The path to the entity asset.
    ///
    /// \throws Error If the scene does not have access to an asset cache.
    Entity createEntity(const Path& path);

    ///
    /// Registers a component with a serializer.
    ///
    /// \param componentTypeName The type name of the component.
    ///
    /// \throws Error If the component type is already registered.
    template <typename T, typename S>
    void registerComponent(const std::string& componentTypeName);

private:
    void _destroyEntity(Entity& entity);

    void _activateEntity(Entity& entity);
    void _deactivateEntity(Entity& entity);

    bool _isActivated(const Entity& entity) const;
    bool _isNull(const Entity& entity) const;

    template <typename T>
    bool _hasComponent(const Entity& entity) const;

    template <typename T>
    T& _addComponent(Entity& entity, const std::shared_ptr<BaseComponent>& component);

    void _addComponentManually(Entity& entity, const std::shared_ptr<BaseComponent>& component);

    template <typename T>
    T& _component(const Entity& entity);

    Engine* _engine;
    AssetCache* _assetCache;

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
    std::vector<std::map<ComponentTypeId, std::shared_ptr<BaseComponent>>> _components;
    
    // Entities deactivated since the last call to refresh()
    std::vector<Entity> _deactivatedEntities;

    // Entities activated since the last call to refresh()
    std::vector<Entity> _activatedEntities;

    // Entities destoryed since the last call to refresh()
    std::vector<Entity> _destroyedEntities;

    // Systems involved in the scene
    std::vector<System*> _systems;

    // Component type names mapped to component types
    std::map<std::string, ComponentTypeId> _componentTypes;

    // Component types mapped to registered component serializers
    std::map<ComponentTypeId, std::shared_ptr<BaseComponentSerializer>> _componentSerializers;

    // Component types mapped to component constructors
    std::map<ComponentTypeId, std::function<std::shared_ptr<BaseComponent>()>> _componentConstructors;
};

}

#include "Scene.inl"