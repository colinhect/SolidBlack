#include "Hect.h"

using namespace hect;

MemoryWriteStream::MemoryWriteStream(std::vector<uint8_t>& data) :
    _data(&data),
    _position(data.size())
{
}

void MemoryWriteStream::writeBytes(const uint8_t* bytes, size_t byteCount)
{
    assert(bytes);

    for (size_t i = 0; i < byteCount; ++i)
    {
        _data->push_back(0);
    }

    std::memcpy(&(*_data)[_position], bytes, byteCount);
    _position += byteCount;
}