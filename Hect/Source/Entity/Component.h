#pragma once

namespace hect
{

class Entity;

///
/// A number identifying a component type.
typedef uint32_t ComponentTypeId;

///
/// Base entity component.
class BaseComponent
{
    friend class Scene;
public:

    ///
    /// A shared reference to a base component.
    typedef std::shared_ptr<BaseComponent> Ref;

    static ComponentTypeId nextTypeId();

    BaseComponent();
    virtual ~BaseComponent() { }

    ///
    /// Returns whether the component is attached to an activated entity.
    bool hasEntity() const;

    ///
    /// Returns the entity that the component belongs to.
    Entity entity() const;

protected:

    virtual ComponentTypeId _componentTypeId() const = 0;

private:
    void _activate(Entity& entity);
    void _deactivate(Entity& entity);

    Scene* _scene;
    uint32_t _entityId;
};

///
/// A typed entity component.
template <typename T>
class Component :
    public BaseComponent
{
public:

    ///
    /// Returns the component type ID for this type of component.
    static ComponentTypeId typeId();

private:

    ComponentTypeId _componentTypeId() const;
};

}

#include "Component.inl"
