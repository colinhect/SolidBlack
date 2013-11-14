#include "Hect.h"

using namespace hect;

void WriteStream::writeString(const std::string& string)
{
    size_t length = string.size();
    writeUnsignedInt((uint32_t)length);
    writeBytes((uint8_t*)&string[0], length);
}

void WriteStream::writeByte(int8_t value)
{
    writeBytes((const uint8_t*)&value, 1);
}

void WriteStream::writeUnsignedByte(uint8_t value)
{
    writeBytes((const uint8_t*)&value, 1);
}

void WriteStream::writeShort(int16_t value)
{
    writeBytes((const uint8_t*)&value, 2);
}

void WriteStream::writeUnsignedShort(uint16_t value)
{
    writeBytes((const uint8_t*)&value, 2);
}

void WriteStream::writeInt(int32_t value)
{
    writeBytes((const uint8_t*)&value, 4);
}

void WriteStream::writeUnsignedInt(uint32_t value)
{
    writeBytes((const uint8_t*)&value, 4);
}

void WriteStream::writeLong(int64_t value)
{
    writeBytes((const uint8_t*)&value, 8);
}

void WriteStream::writeUnsignedLong(uint64_t value)
{
    writeBytes((const uint8_t*)&value, 8);
}

void WriteStream::writeFloat(float value)
{
    writeBytes((const uint8_t*)&value, 4);
}

void WriteStream::writeDouble(double value)
{
    writeBytes((const uint8_t*)&value, 8);
}