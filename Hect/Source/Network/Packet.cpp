#include "Hect.h"

using namespace hect;

Packet::Packet(uint8_t flags) :
    _flags(flags)
{
}

bool Packet::hasFlag(Flag flag) const
{
    return (_flags & flag) == flag;
}

Packet::Data& Packet::data()
{
    return _data;
}

const Packet::Data& Packet::data() const
{
    return _data;
}