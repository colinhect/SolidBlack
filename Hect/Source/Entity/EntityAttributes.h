#pragma once

namespace hect
{
enum class EntityAttributeBit
{
    MarkedForDestruction = 59,
    MarkedForActivation = 60,
    MarkedForDeactivation = 61,
    Activated = 62,
    Exists = 63
};

class EntityAttributes
{
public:
    bool hasAttribute(EntityAttributeBit attribute) const;
    void setAttribute(EntityAttributeBit attribute, bool value);

    bool hasComponent(ComponentTypeId type) const;
    void setHasComponent(ComponentTypeId type, bool value);

    bool contains(const EntityAttributes& attributes) const;

    EntityAttributes difference(const EntityAttributes& attributes) const;

private:
    std::bitset<64> _bitset;
};

}