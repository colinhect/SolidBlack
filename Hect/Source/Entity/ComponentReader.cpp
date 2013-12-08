#include "Hect.h"

using namespace hect;

DataValueComponentReader::DataValueComponentReader(const DataValue& dataValue)
{
    _dataValueStack.push(dataValue);
}

bool DataValueComponentReader::beginObject(const char* name)
{
    _dataValueStack.push(_dataValueStack.top()[name]);
    return !_dataValueStack.top().isNull();
}

void DataValueComponentReader::endObject()
{
    _dataValueStack.pop();
}

bool DataValueComponentReader::hasMember(const char* name)
{
    return !_dataValueStack.top()[name].isNull();
}

double DataValueComponentReader::readMemberDouble(const char* name)
{
    return _dataValueStack.top()[name].asDouble();
}

std::string DataValueComponentReader::readMemberString(const char* name)
{
    return _dataValueStack.top()[name].asString();
}

Vector2<> DataValueComponentReader::readMemberVector2(const char* name)
{
    return _dataValueStack.top()[name].asVector2();
}

Vector3<> DataValueComponentReader::readMemberVector3(const char* name)
{
    return _dataValueStack.top()[name].asVector3();
}

Vector4<> DataValueComponentReader::readMemberVector4(const char* name)
{
    return _dataValueStack.top()[name].asVector4();
}

Quaternion<> DataValueComponentReader::readMemberQuaternion(const char* name)
{
    return _dataValueStack.top()[name].asQuaternion();
}

BinaryComponentReader::BinaryComponentReader(ReadStream& stream) :
    _stream(&stream)
{
}

bool BinaryComponentReader::beginObject(const char* name)
{
    name;
    return true;
}

void BinaryComponentReader::endObject()
{
}

bool BinaryComponentReader::hasMember(const char* name)
{
    name;
    return true; // Assume that all values are written
}

double BinaryComponentReader::readMemberDouble(const char* name)
{
    name;
    return _stream->readDouble();
}

std::string BinaryComponentReader::readMemberString(const char* name)
{
    name;
    return _stream->readString();
}

Vector2<> BinaryComponentReader::readMemberVector2(const char* name)
{
    name;
    return _stream->readVector2();
}

Vector3<> BinaryComponentReader::readMemberVector3(const char* name)
{
    name;
    return _stream->readVector3();
}

Vector4<> BinaryComponentReader::readMemberVector4(const char* name)
{
    name;
    return _stream->readVector4();
}

Quaternion<> BinaryComponentReader::readMemberQuaternion(const char* name)
{
    name;
    return _stream->readQuaternion();
}