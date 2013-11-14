#include "Hect.h"

using namespace hect;

std::string ReadStream::readString()
{
    size_t byteCount = readUnsignedInt();
    std::string string(byteCount, ' ');
    readBytes((uint8_t*)&string[0], byteCount);
    return string;
}

std::string ReadStream::readAllToString()
{
    size_t byteCount = length();
    std::string string(byteCount, ' ');
    readBytes((uint8_t*)&string[0], byteCount);
    return string;
}

int8_t ReadStream::readByte()
{
    int8_t value = 0;
    readBytes((uint8_t*)&value, 1);
    return value;
}

uint8_t ReadStream::readUnsignedByte()
{
    uint8_t value = 0;
    readBytes((uint8_t*)&value, 1);
    return value;
}

int16_t ReadStream::readShort()
{
    int16_t value = 0;
    readBytes((uint8_t*)&value, 2);
    return value;
}

uint16_t ReadStream::readUnsignedShort()
{
    uint16_t value = 0;
    readBytes((uint8_t*)&value, 2);
    return value;
}

int32_t ReadStream::readInt()
{
    int32_t value = 0;
    readBytes((uint8_t*)&value, 4);
    return value;
}

uint32_t ReadStream::readUnsignedInt()
{
    uint32_t value = 0;
    readBytes((uint8_t*)&value, 4);
    return value;
}

int64_t ReadStream::readLong()
{
    int64_t value = 0;
    readBytes((uint8_t*)&value, 8);
    return value;
}

uint64_t ReadStream::readUnsignedLong()
{
    uint64_t value = 0;
    readBytes((uint8_t*)&value, 8);
    return value;
}

float ReadStream::readFloat()
{
    float value = 0;
    readBytes((uint8_t*)&value, 4);
    return value;
}

double ReadStream::readDouble()
{
    double value = 0;
    readBytes((uint8_t*)&value, 8);
    return value;
}