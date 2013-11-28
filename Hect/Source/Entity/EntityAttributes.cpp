#include "Hect.h"

using namespace hect;

bool EntityAttributes::hasAttribute(EntityAttributeBit attribute) const
{
    return _bitset.test((size_t)attribute);
}

void EntityAttributes::setAttribute(EntityAttributeBit attribute, bool value)
{
    _bitset.set((size_t)attribute, value);
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

EntityAttributes EntityAttributes::difference(const EntityAttributes& attributes) const
{
    uint64_t theseAttributes = _bitset.to_ullong();
    uint64_t thoseAttributes = attributes._bitset.to_ullong();

    uint64_t mask = theseAttributes ^ thoseAttributes;

    EntityAttributes result;
    result._bitset = theseAttributes & mask;

    return result;
}