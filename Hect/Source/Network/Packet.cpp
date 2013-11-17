#include "Hect.h"

using namespace hect;

Packet::Packet(uint8_t flags) :
    _flags(flags)
{
}

PacketReadStream Packet::readStream() const
{
    return PacketReadStream(_data);
}

PacketWriteStream Packet::writeStream()
{
    return PacketWriteStream(_data);
}

Packet::Packet(const std::vector<uint8_t>& data) :
    _data(data),
    _flags(0)
{
}