#include "Hect.h"

using namespace hect;

MemoryReadStream::MemoryReadStream(const std::vector<uint8_t>& data) :
    _data(&data),
    _position(0)
{
}

void MemoryReadStream::readBytes(uint8_t* bytes, size_t byteCount)
{
    assert(bytes);

    size_t length = this->length();
    size_t position = this->position();

    if (position + byteCount >= length + 1)
    {
        throw Error("Attempt to read past end of data");
    }

    std::memcpy(bytes, &(*_data)[position], byteCount);
    _position += byteCount;
}

bool MemoryReadStream::endOfStream() const
{
    return _position >= length();
}

size_t MemoryReadStream::length() const
{
    return _data->size();
}

size_t MemoryReadStream::position() const
{
    return _position;
}

void MemoryReadStream::seek(size_t position)
{
    size_t length = this->length();

    if (position >= length + 1)
    {
        throw Error("Attempt to seek past end of data");
    }

    _position = position;
}