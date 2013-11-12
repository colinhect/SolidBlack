#include "Hect.h"

using namespace hect;

void WriteStream::writeString(const std::string& string)
{
    size_t length = string.size();
    writeUnsigned32((uint32_t)length);
    writeBytes((uint8_t*)&string[0], length);
}

void WriteStream::writeSigned8(int8_t value)
{
    writeBytes((const uint8_t*)&value, 1);
}

void WriteStream::writeUnsigned8(uint8_t value)
{
    writeBytes((const uint8_t*)&value, 1);
}

void WriteStream::writeSigned16(int16_t value)
{
    writeBytes((const uint8_t*)&value, 2);
}

void WriteStream::writeUnsigned16(uint16_t value)
{
    writeBytes((const uint8_t*)&value, 2);
}

void WriteStream::writeSigned32(int32_t value)
{
    writeBytes((const uint8_t*)&value, 4);
}

void WriteStream::writeUnsigned32(uint32_t value)
{
    writeBytes((const uint8_t*)&value, 4);
}

void WriteStream::writeSigned64(int64_t value)
{
    writeBytes((const uint8_t*)&value, 8);
}

void WriteStream::writeUnsigned64(uint64_t value)
{
    writeBytes((const uint8_t*)&value, 8);
}

void WriteStream::writeFloat32(float value)
{
    writeBytes((const uint8_t*)&value, 4);
}

void WriteStream::writeFloat64(double value)
{
    writeBytes((const uint8_t*)&value, 8);
}