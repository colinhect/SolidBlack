#include "Hect.h"

using namespace hect;

void DataValueComponentWriter::writeDouble(const char* name, double value)
{
    _members[name] = value;
}

void DataValueComponentWriter::writeString(const char* name, const std::string& value)
{
    _members[name] = value;
}

void DataValueComponentWriter::writeVector2(const char* name, const Vector2<>& value)
{
    _members[name] = value;
}

void DataValueComponentWriter::writeVector3(const char* name, const Vector3<>& value)
{
    _members[name] = value;
}

void DataValueComponentWriter::writeVector4(const char* name, const Vector4<>& value)
{
    _members[name] = value;
}

void DataValueComponentWriter::writeQuaternion(const char* name, const Quaternion<>& value)
{
    _members[name] = value;
}

DataValue DataValueComponentWriter::dataValue() const
{
    return DataValue(_members);
}

BinaryComponentWriter::BinaryComponentWriter(WriteStream& stream) :
    _stream(&stream)
{
}

void BinaryComponentWriter::writeDouble(const char* name, double value)
{
    name;
    _stream->writeDouble(value);
}

void BinaryComponentWriter::writeString(const char* name, const std::string& value)
{
    name;
    _stream->writeString(value);
}

void BinaryComponentWriter::writeVector2(const char* name, const Vector2<>& value)
{
    name;
    _stream->writeVector2(value);
}

void BinaryComponentWriter::writeVector3(const char* name, const Vector3<>& value)
{
    name;
    _stream->writeVector3(value);
}

void BinaryComponentWriter::writeVector4(const char* name, const Vector4<>& value)
{
    name;
    _stream->writeVector4(value);
}

void BinaryComponentWriter::writeQuaternion(const char* name, const Quaternion<>& value)
{
    name;
    _stream->writeQuaternion(value);
}