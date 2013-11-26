#include "Hect.h"

using namespace hect;

Scene::Scene(InputSystem& inputSystem) :
    _input(&inputSystem),
    _assetCache(nullptr),
    _nextId(1),
    _deactivatedAttributes(InitialPoolSize),
    _attributes(InitialPoolSize),
    _components(InitialPoolSize)
{
    _registerComponents();
}

Scene::Scene(InputSystem& inputSystem, AssetCache& assetCache) :
    _input(&inputSystem),
    _assetCache(&assetCache),
    _nextId(1),
    _deactivatedAttributes(InitialPoolSize),
    _attributes(InitialPoolSize),
    _components(InitialPoolSize)
{
    _registerComponents();
}

Scene::~Scene()
{
    for (System* system : _systems)
    {
        system->removeAllEntities();
    }
}

void Scene::refresh()
{
    for (Entity& entity : _deactivatedEntities)
    {
        EntityAttributes& deactivatedAttributes = _deactivatedAttributes[entity._id];
        EntityAttributes& attributes = _attributes[entity._id];
        bool wasReactivated = attributes.hasAttribute(EntityAttribute::Activated);

        // The entity was deactivated and reactivated since last refresh
        if (wasReactivated)
        {
            EntityAttributes difference = deactivatedAttributes.difference(attributes);

            // Remove the entity from all systems where it was effectively removed from
            for (System* system : _systems)
            {
                if (system->requiredAttributes().contains(difference))
                {
                    system->removeEntity(entity);
                }
            }
        }

        // The entity was deactivated but not reactivated since last refresh
        else
        {
            // Remove the entity from all systems it was in on deactivation
            for (System* system : _systems)
            {
                if (deactivatedAttributes.contains(system->requiredAttributes()))
                {
                    system->removeEntity(entity);
                }
            }
        }
        
        attributes.setAttribute(EntityAttribute::MarkedForDeactivation, false);
        attributes.setAttribute(EntityAttribute::Activated, false);
    }
    _deactivatedEntities.clear();

    // Add all recently activated entities to the systems they belong to
    for (Entity& entity : _activatedEntities)
    {
        EntityAttributes& attributes = _attributes[entity._id];

        for (System* system : _systems)
        {
            if (attributes.contains(system->requiredAttributes()))
            {
                system->addEntity(entity);
            }
        }
        
        attributes.setAttribute(EntityAttribute::MarkedForActivation, false);
        attributes.setAttribute(EntityAttribute::Activated, true);
    }
    _activatedEntities.clear();

    for (Entity& entity : _destroyedEntities)
    {
        // Clear entity component/attribute data
        Entity::Id id = entity._id;
        _components[id].clear();
        _attributes[id] = EntityAttributes();

        // Re-use this ID
        _nextIds.push(id);
    }
    _destroyedEntities.clear();
}

InputSystem& Scene::inputSystem()
{
    return *_input;
}

void Scene::addSystem(System& system)
{
    _systems.push_back(&system);

    // Add any entities the systems is filtered for
    size_t entityCount = _attributes.size();
    for (Entity::Id id = 1; id < entityCount; ++id)
    {
        EntityAttributes& attributes = _attributes[id];
        if (attributes.hasAttribute(EntityAttribute::Exists) && attributes.contains(system.requiredAttributes()))
        {
            system.addEntity(Entity(*this, id));
        }
    }
}

void Scene::removeSystem(System& system)
{
    system.removeAllEntities();
    _systems.erase(std::remove(_systems.begin(), _systems.end(), &system), _systems.end());
}

Entity Scene::createEntity()
{
    Entity::Id id;

    // Re-use IDs as often as possible to avoid resizing the pool
    if (!_nextIds.empty())
    {
        id = _nextIds.back();
        _nextIds.pop();
    }
    else
    {
        id = _nextId++;

        // Resize the pool if needed
        if (id >= _components.size())
        {
            _growPool();
        }
    }

    Entity entity(*this, id);
    _attributes[id].setAttribute(EntityAttribute::Exists, true);
    return entity;
}

Entity Scene::createEntity(const Path& path)
{
    if (!_assetCache)
    {
        throw Error("Cannot create an entity from a file without an asset cache");
    }

    Entity entity = createEntity();

    const DataValue& dataValue = *_assetCache->get<DataValue>(path);
    for (const std::string& componentTypeName : dataValue.memberNames())
    {
        if (_componentTypes.find(componentTypeName) == _componentTypes.end())
        {
            throw Error(format("No serializer registered for component type '%s'", componentTypeName.c_str()));
        }

        ComponentTypeId type = _componentTypes[componentTypeName];

        std::shared_ptr<BaseComponent> component = _componentConstructors[type]();
        _componentSerializers[type]->_deserialize(component.get(), dataValue[componentTypeName], *_assetCache);
        _addComponentManually(entity, component);
    }

    entity.activate();
    return entity;
}

void Scene::_destroyEntity(Entity& entity)
{
    EntityAttributes& attributes = _attributes[entity._id];

#ifdef HECT_DEBUG
    if (_isNull(entity))
    {
        throw Error("Attempt to destroy a null entity");
    }
    else if (attributes.hasAttribute(EntityAttribute::MarkedForDestruction))
    {
        throw Error("Entity is already marked for destruction");
    }
#endif

    attributes.setAttribute(EntityAttribute::MarkedForDestruction, true);

    if (_isActivated(entity) && !attributes.hasAttribute(EntityAttribute::MarkedForDeactivation))
    {
        _deactivateEntity(entity);
    }

    _destroyedEntities.push_back(entity);
}

void Scene::_activateEntity(Entity& entity)
{
    EntityAttributes& attributes = _attributes[entity._id];

#ifdef HECT_DEBUG
    if (_isActivated(entity) && !attributes.hasAttribute(EntityAttribute::MarkedForDeactivation))
    {
        throw Error("Entity is already activated");
    }
    else if (attributes.hasAttribute(EntityAttribute::MarkedForActivation))
    {
        throw Error("Entity is already marked for activation");
    }
#endif

    attributes.setAttribute(EntityAttribute::MarkedForActivation, true);

    // Call onActivate() for all components
    auto& components = _components[entity._id];
    for (auto& pair : components)
    {
        pair.second->onActivate(entity);
    }

    _activatedEntities.push_back(entity);
}

void Scene::_deactivateEntity(Entity& entity)
{
    EntityAttributes& attributes = _attributes[entity._id];

#ifdef HECT_DEBUG
    if (!_isActivated(entity))
    {
        throw Error("Entity is already deactivated");
    }
    else if (attributes.hasAttribute(EntityAttribute::MarkedForDeactivation))
    {
        throw Error("Entity is already marked for deactivation");
    }
#endif

    attributes.setAttribute(EntityAttribute::MarkedForDeactivation, true);

    // Call onDeactivate() for all components
    auto& components = _components[entity._id];
    for (auto& pair : components)
    {
        pair.second->onDeactivate(entity);
    }

    // Keep the attributes the entity had on deactivation
    _deactivatedAttributes[entity._id] = _attributes[entity._id];
    _deactivatedEntities.push_back(entity);
}

bool Scene::_isActivated(const Entity& entity) const
{
    return _attributes[entity._id].hasAttribute(EntityAttribute::Activated);
}

bool Scene::_isNull(const Entity& entity) const
{
    return !_attributes[entity._id].hasAttribute(EntityAttribute::Exists);
}

void Scene::_addComponentManually(Entity& entity, const std::shared_ptr<BaseComponent>& component)
{
    ComponentTypeId type = component->componentTypeId();

#ifdef HECT_DEBUG
    assert(!entity.isNull());
    if(_attributes[entity._id].hasComponent(type))
    {
        throw Error("Attempt to add a component an entity already has");
    }

    if (_isActivated(entity))
    {
        throw Error("Attempt to add a component to an activated entity");
    }
#endif

    // Add the existence of a component of this type to the entity's attributes
    _attributes[entity._id].setHasComponent(type, true);

    // Add the component to the entity's components
    _components[entity._id][type] = component;
}

void Scene::_registerComponents()
{
    registerComponent<Camera, CameraSerializer>("Camera");
    registerComponent<Geometry, GeometrySerializer>("Geometry");
    registerComponent<Transform, TransformSerializer>("Transform");
}

void Scene::_growPool()
{
    size_t size = _components.size() * 2;
    _deactivatedAttributes.resize(size);
    _attributes.resize(size);
    _components.resize(size);
}