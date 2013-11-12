#include "Hect.h"

using namespace hect;

// Bits 0-61 are used for component existence by type
const size_t _nullBit = 63;
const size_t _activatedBit = 62;

bool EntityAttributes::isNull() const
{
    return !_bitField.get(_nullBit);
}

void EntityAttributes::setNull(bool value)
{
    _bitField.set(_nullBit, !value);
}

bool EntityAttributes::isActivated() const
{
    return _bitField.get(_activatedBit);
}

void EntityAttributes::setActivated(bool value)
{
    _bitField.set(_activatedBit, value);
}

bool EntityAttributes::hasComponent(EntityComponentType type) const
{
    return _bitField.get(type);
}

void EntityAttributes::setHasComponent(EntityComponentType type, bool value)
{
    _bitField.set(type, value);
}

bool EntityAttributes::contains(const EntityAttributes& attributes) const
{
    return _bitField.contains(attributes._bitField);
}