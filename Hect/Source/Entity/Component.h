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
    BaseComponent(const BaseComponent& component);
    virtual ~BaseComponent() { }

    ///
    /// Returns whether the component is attached to an activated entity.
    bool hasEntity() const;

    ///
    /// Returns the entity that the component belongs to.
    Entity entity() const;

protected:

    virtual BaseComponent::Ref _clone() const = 0;
    virtual ComponentTypeId _componentTypeId() const = 0;

private:
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
    BaseComponent::Ref _clone() const;
    ComponentTypeId _componentTypeId() const;
};

}

#include "Component.inl"
