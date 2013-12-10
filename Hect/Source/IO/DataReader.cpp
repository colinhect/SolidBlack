#include "Hect.h"

using namespace hect;

DataValueReader::DataValueReader(const DataValue& dataValue)
{
    _dataValueStack.push(dataValue);
}

bool DataValueReader::beginObject(const char* memberName)
{
    _dataValueStack.push(_dataValueStack.top()[memberName]);
    return !_dataValueStack.top().isNull();
}

void DataValueReader::endObject()
{
    _dataValueStack.pop();
}

bool DataValueReader::hasMember(const char* memberName)
{
    return !_dataValueStack.top()[memberName].isNull();
}

double DataValueReader::readDouble(const char* memberName)
{
    return _dataValueStack.top()[memberName].asDouble();
}

std::string DataValueReader::readString(const char* memberName)
{
    return _dataValueStack.top()[memberName].asString();
}

Vector2<> DataValueReader::readVector2(const char* memberName)
{
    return _dataValueStack.top()[memberName].asVector2();
}

Vector3<> DataValueReader::readVector3(const char* memberName)
{
    return _dataValueStack.top()[memberName].asVector3();
}

Vector4<> DataValueReader::readVector4(const char* memberName)
{
    return _dataValueStack.top()[memberName].asVector4();
}

BinaryDataReader::BinaryDataReader(ReadStream& stream) :
    _stream(&stream)
{
}

bool BinaryDataReader::beginObject(const char* memberName)
{
    memberName;
    return true;
}

void BinaryDataReader::endObject()
{
}

bool BinaryDataReader::hasMember(const char* memberName)
{
    memberName;
    return true; // Assume that all values are written
}

double BinaryDataReader::readDouble(const char* memberName)
{
    memberName;
    return _stream->readDouble();
}

std::string BinaryDataReader::readString(const char* memberName)
{
    memberName;
    return _stream->readString();
}

Vector2<> BinaryDataReader::readVector2(const char* memberName)
{
    memberName;
    return _stream->readVector2();
}

Vector3<> BinaryDataReader::readVector3(const char* memberName)
{
    memberName;
    return _stream->readVector3();
}

Vector4<> BinaryDataReader::readVector4(const char* memberName)
{
    memberName;
    return _stream->readVector4();
}