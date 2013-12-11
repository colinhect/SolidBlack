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

    while (_position + byteCount > _data->size())
    {
        _data->push_back(0);
    }

    std::memcpy(&(*_data)[_position], bytes, byteCount);
    _position += byteCount;
}

size_t MemoryWriteStream::position() const
{
    return _position;
}

void MemoryWriteStream::seek(size_t position)
{
    size_t length = _data->size();

    if (position >= length + 1)
    {
        throw Error("Attempt to seek past end of data");
    }

    _position = position;
}