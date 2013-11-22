#include "Hect.h"

using namespace hect;

// Bits 0-61 are used for component existence by type
const size_t _nullBit = 63;
const size_t _activatedBit = 62;

bool EntityAttributes::isNull() const
{
    return !_bitset.test(_nullBit);
}

void EntityAttributes::setNull(bool value)
{
    _bitset.set(_nullBit, !value);
}

bool EntityAttributes::isActivated() const
{
    return _bitset.test(_activatedBit);
}

void EntityAttributes::setActivated(bool value)
{
    _bitset.set(_activatedBit, value);
}

bool EntityAttributes::hasComponent(ComponentType type) const
{
    return _bitset.test(type);
}

void EntityAttributes::setHasComponent(ComponentType type, bool value)
{
    _bitset.set(type, value);
}

bool EntityAttributes::contains(const EntityAttributes& attributes) const
{
    uint64_t theseAttributes = _bitset.to_ullong();
    uint64_t thoseAttributes = attributes._bitset.to_ullong();
    return (theseAttributes & thoseAttributes) == thoseAttributes;
}