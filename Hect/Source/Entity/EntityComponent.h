#pragma once

namespace hect
{

class Entity;

///
/// A number identifying a component type.
typedef uint32_t EntityComponentType;

///
/// Base entity component.
class BaseComponent
{
public:
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
    virtual EntityComponentType componentType() const = 0;

    ///
    /// Returns the next valid component type.
    static EntityComponentType nextType();
};

///
/// A typed entity component.
template <typename T>
class EntityComponent :
    public BaseComponent
{
public:

    ///
    /// \copydoc BaseComponent::componentType()
    EntityComponentType componentType() const;

    ///
    /// Returns the component type for this type of component.
    static EntityComponentType type();
};

}

#include "EntityComponent.inl"
