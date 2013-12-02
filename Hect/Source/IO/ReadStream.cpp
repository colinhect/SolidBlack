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

Vector2<> ReadStream::readVector2()
{
    double x = readDouble();
    double y = readDouble();
    return Vector2<>(x, y);
}
    
Vector3<> ReadStream::readVector3()
{
    double x = readDouble();
    double y = readDouble();
    double z = readDouble();
    return Vector3<>(x, y, z);
}

Vector4<> ReadStream::readVector4()
{
    double x = readDouble();
    double y = readDouble();
    double z = readDouble();
    double w = readDouble();
    return Vector4<>(x, y, z, w);
}

Quaternion<> ReadStream::readQuaternion()
{
    double x = readDouble();
    double y = readDouble();
    double z = readDouble();
    double w = readDouble();
    return Quaternion<>(x, y, z, w);
}