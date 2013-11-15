#include "Hect.h"

using namespace hect;

Packet::Packet(uint8_t flags) :
    _flags(flags)
{
}

MemoryReadStream Packet::readStream() const
{
    return MemoryReadStream(_data);
}

MemoryWriteStream Packet::writeStream()
{
    return MemoryWriteStream(_data);
}

Packet::Packet(const std::vector<uint8_t>& data) :
    _data(data),
    _flags(0)
{
}