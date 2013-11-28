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
public:

    ///
    /// A shared reference to a base component.
    typedef std::shared_ptr<BaseComponent> Ref;

    virtual ~BaseComponent() { }

    ///
    /// Called when the entity of the component is activated.
    ///
    /// \param entity The entity of the component.
    virtual void onActivate(Entity& entity) { }

    ///
    /// Called when the entity of the component is deactivated.
    ///
    /// \param entity The entity of the component.
    virtual void onDeactivate(Entity& entity) { }

    ///
    /// Returns the component type of the component.
    virtual ComponentTypeId componentTypeId() const = 0;

    ///
    /// Returns the next valid component type.
    static ComponentTypeId nextTypeId();
};

///
/// A typed entity component.
template <typename T>
class Component :
    public BaseComponent
{
public:

    ///
    /// \copydoc BaseComponent::componentTypeId()
    ComponentTypeId componentTypeId() const;

    ///
    /// Returns the component type ID for this type of component.
    static ComponentTypeId typeId();
};

}

#include "Component.inl"
