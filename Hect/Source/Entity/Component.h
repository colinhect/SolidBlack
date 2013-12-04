#pragma once

namespace hect
{

class Entity;
class Scene;

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

    ///
    /// Returns the next available component type id.
    static ComponentTypeId nextTypeId();

    ///
    /// Virtual destructor.
    virtual ~BaseComponent() { }

    ///
    /// Clones the component.
    virtual BaseComponent* clone() const = 0;

    ///
    /// Returns the type id of the component.
    virtual ComponentTypeId componentTypeId() const = 0;
};

///
/// A typed entity component.
template <typename T>
class Component :
    public BaseComponent
{
public:

    ///
    /// Returns the component type id for this type of component.
    static ComponentTypeId typeId();

    ///
    /// \copydoc BaseComponent::clone()
    BaseComponent* clone() const;

    ///
    /// \copydoc BaseComponent::componentTypeId()
    ComponentTypeId componentTypeId() const;
};

}

#include "Component.inl"
