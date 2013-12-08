#include "Hect.h"

using namespace hect;

DataValueComponentReader::DataValueComponentReader(const DataValue& dataValue) :
    _dataValue(&dataValue)
{
}

bool DataValueComponentReader::hasValue(const char* name)
{
    return !(*_dataValue)[name].isNull();
}

double DataValueComponentReader::readDouble(const char* name)
{
    return (*_dataValue)[name].asDouble();
}

std::string DataValueComponentReader::readString(const char* name)
{
    return (*_dataValue)[name].asString();
}

Vector2<> DataValueComponentReader::readVector2(const char* name)
{
    return (*_dataValue)[name].asVector2();
}

Vector3<> DataValueComponentReader::readVector3(const char* name)
{
    return (*_dataValue)[name].asVector3();
}

Vector4<> DataValueComponentReader::readVector4(const char* name)
{
    return (*_dataValue)[name].asVector4();
}

Quaternion<> DataValueComponentReader::readQuaternion(const char* name)
{
    return (*_dataValue)[name].asQuaternion();
}

BinaryComponentReader::BinaryComponentReader(ReadStream& stream) :
    _stream(&stream)
{
}

bool BinaryComponentReader::hasValue(const char* name)
{
    name;
    return true; // Assume that all values are written
}

double BinaryComponentReader::readDouble(const char* name)
{
    name;
    return _stream->readDouble();
}

std::string BinaryComponentReader::readString(const char* name)
{
    name;
    return _stream->readString();
}

Vector2<> BinaryComponentReader::readVector2(const char* name)
{
    name;
    return _stream->readVector2();
}

Vector3<> BinaryComponentReader::readVector3(const char* name)
{
    name;
    return _stream->readVector3();
}

Vector4<> BinaryComponentReader::readVector4(const char* name)
{
    name;
    return _stream->readVector4();
}

Quaternion<> BinaryComponentReader::readQuaternion(const char* name)
{
    name;
    return _stream->readQuaternion();
}