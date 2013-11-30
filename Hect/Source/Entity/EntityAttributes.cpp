#include "Hect.h"

using namespace hect;

enum class EntityAttributeBit
{
    Destroyed = 61,
    Activated = 62,
    NotNull = 63
};

bool EntityAttributes::isActivated() const
{
    return _bitset.test((size_t)EntityAttributeBit::Activated);
}

void EntityAttributes::setActivated(bool activated)
{
    _bitset.set((size_t)EntityAttributeBit::Activated, activated);
}

bool EntityAttributes::isDestroyed() const
{
    return _bitset.test((size_t)EntityAttributeBit::Destroyed);
}

void EntityAttributes::setDestroyed(bool destroyed)
{
    _bitset.set((size_t)EntityAttributeBit::Destroyed, destroyed);
}

bool EntityAttributes::isNull() const
{
    return !_bitset.test((size_t)EntityAttributeBit::NotNull);
}

void EntityAttributes::setNull(bool null)
{
    _bitset.set((size_t)EntityAttributeBit::NotNull, !null);
}

bool EntityAttributes::hasComponent(ComponentTypeId type) const
{
    return _bitset.test(type);
}

void EntityAttributes::setHasComponent(ComponentTypeId type, bool value)
{
    _bitset.set(type, value);
}

bool EntityAttributes::contains(const EntityAttributes& attributes) const
{
    uint64_t theseAttributes = _bitset.to_ullong();
    uint64_t thoseAttributes = attributes._bitset.to_ullong();
    return (theseAttributes & thoseAttributes) == thoseAttributes;
}