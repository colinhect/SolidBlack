#include "Hect.h"

using namespace hect;

enum class EntityDataBit
{
    NotSerializable = 60,
    Destroyed = 61,
    Activated = 62,
    NotNull = 63
};

bool EntityData::isActivated() const
{
    return _bitset.test((size_t)EntityDataBit::Activated);
}

void EntityData::setActivated(bool activated)
{
    _bitset.set((size_t)EntityDataBit::Activated, activated);
}

bool EntityData::isDestroyed() const
{
    return _bitset.test((size_t)EntityDataBit::Destroyed);
}

void EntityData::setDestroyed(bool destroyed)
{
    _bitset.set((size_t)EntityDataBit::Destroyed, destroyed);
}

bool EntityData::isNull() const
{
    return !_bitset.test((size_t)EntityDataBit::NotNull);
}

void EntityData::setNull(bool null)
{
    _bitset.set((size_t)EntityDataBit::NotNull, !null);
}

bool EntityData::isSerializable() const
{
    return !_bitset.test((size_t)EntityDataBit::NotSerializable);
}

void EntityData::setSerializable(bool serializable)
{
    _bitset.set((size_t)EntityDataBit::NotSerializable, !serializable);
}

bool EntityData::hasComponent(ComponentTypeId typeId) const
{
    return _bitset.test(typeId);
}

void EntityData::setHasComponent(ComponentTypeId typeId, bool value)
{
    _bitset.set(typeId, value);
}