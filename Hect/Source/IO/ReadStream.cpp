#include "Hect.h"

using namespace hect;

std::string ReadStream::readString()
{
    size_t byteCount = readUnsigned32();
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

int8_t ReadStream::readSigned8()
{
    int8_t value = 0;
    readBytes((uint8_t*)&value, 1);
    return value;
}

uint8_t ReadStream::readUnsigned8()
{
    uint8_t value = 0;
    readBytes((uint8_t*)&value, 1);
    return value;
}

int16_t ReadStream::readSigned16()
{
    int16_t value = 0;
    readBytes((uint8_t*)&value, 2);
    return value;
}

uint16_t ReadStream::readUnsigned16()
{
    uint16_t value = 0;
    readBytes((uint8_t*)&value, 2);
    return value;
}

int32_t ReadStream::readSigned32()
{
    int32_t value = 0;
    readBytes((uint8_t*)&value, 4);
    return value;
}

uint32_t ReadStream::readUnsigned32()
{
    uint32_t value = 0;
    readBytes((uint8_t*)&value, 4);
    return value;
}

int64_t ReadStream::readSigned64()
{
    int64_t value = 0;
    readBytes((uint8_t*)&value, 8);
    return value;
}

uint64_t ReadStream::readUnsigned64()
{
    uint64_t value = 0;
    readBytes((uint8_t*)&value, 8);
    return value;
}

float ReadStream::readFloat32()
{
    float value = 0;
    readBytes((uint8_t*)&value, 4);
    return value;
}

double ReadStream::readFloat64()
{
    double value = 0;
    readBytes((uint8_t*)&value, 8);
    return value;
}