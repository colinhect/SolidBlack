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

    virtual ~BaseComponent() { }

    ///
    /// Clones the component.
    virtual BaseComponent* clone() const = 0;

    ///
    /// Returns the type id of the component.
    virtual ComponentTypeId componentTypeId() const = 0;
};

///
/// A component of an entity.
template <typename T>
class Component :
    public BaseComponent
{
public:

    ///
    /// Returns the component type id for this type of component.
    static ComponentTypeId typeId();

    BaseComponent* clone() const;
    ComponentTypeId componentTypeId() const;
};

}

#include "Component.inl"
