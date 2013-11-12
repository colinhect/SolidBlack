#include "Hect.h"

using namespace hect;

Packet::Packet(bool reliable) :
    _reliable(reliable)
{
}

bool Packet::isReliable() const
{
    return _reliable;
}

Packet::Data& Packet::data()
{
    return _data;
}

const Packet::Data& Packet::data() const
{
    return _data;
}