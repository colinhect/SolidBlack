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
    Scene(InputSystem& inputSystem);

    ///
    /// Constructs a scene given an asset cache.
    ///
    /// \remarks Entity components often need access to engine which is why the
    /// scene is given the engine.
    ///
    /// \param engine The engine.
    /// \param assetCache An asset cache.
    Scene(InputSystem& inputSystem, AssetCache& assetCache);

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

    InputSystem& inputSystem();

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
    T& _addComponent(Entity& entity, const std::shared_ptr<BaseComponent>& component);

    template <typename T>
    void _removeComponent(Entity& entity);

    void _addComponentManually(Entity& entity, const std::shared_ptr<BaseComponent>& component);

    template <typename T>
    T& _component(const Entity& entity);

    void _registerComponents();
    void _growPool();

    InputSystem* _input;
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