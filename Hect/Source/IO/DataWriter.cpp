#include "Hect.h"

using namespace hect;

DataValueWriter::DataValueWriter()
{
    _objectStack.push(DataValue::Object());
}

void DataValueWriter::beginObject(const char* memberName)
{
    _objectNameStack.push(memberName);
    _objectStack.push(DataValue::Object());
}

void DataValueWriter::endObject()
{
    std::string name = _objectNameStack.top();
    _objectNameStack.pop();

    DataValue members = _objectStack.top();
    _objectStack.pop();

    _objectStack.top()[name] = DataValue(members);
}

void DataValueWriter::writeDouble(const char* memberName, double value)
{
    _objectStack.top()[memberName] = value;
}

void DataValueWriter::writeString(const char* memberName, const std::string& value)
{
    _objectStack.top()[memberName] = value;
}

void DataValueWriter::writeVector2(const char* memberName, const Vector2<>& value)
{
    _objectStack.top()[memberName] = value;
}

void DataValueWriter::writeVector3(const char* memberName, const Vector3<>& value)
{
    _objectStack.top()[memberName] = value;
}

void DataValueWriter::writeVector4(const char* memberName, const Vector4<>& value)
{
    _objectStack.top()[memberName] = value;
}

DataValue DataValueWriter::rootDataValue() const
{
    return DataValue(_objectStack.top());
}

BinaryDataWriter::BinaryDataWriter(WriteStream& stream) :
    _stream(&stream)
{
}

void BinaryDataWriter::beginObject(const char* memberName)
{
    memberName;
}

void BinaryDataWriter::endObject()
{
}

void BinaryDataWriter::writeDouble(const char* memberName, double value)
{
    memberName;
    _stream->writeDouble(value);
}

void BinaryDataWriter::writeString(const char* memberName, const std::string& value)
{
    memberName;
    _stream->writeString(value);
}

void BinaryDataWriter::writeVector2(const char* memberName, const Vector2<>& value)
{
    memberName;
    _stream->writeVector2(value);
}

void BinaryDataWriter::writeVector3(const char* memberName, const Vector3<>& value)
{
    memberName;
    _stream->writeVector3(value);
}

void BinaryDataWriter::writeVector4(const char* memberName, const Vector4<>& value)
{
    memberName;
    _stream->writeVector4(value);
}