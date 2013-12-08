#include "Hect.h"

using namespace hect;

DataValueComponentWriter::DataValueComponentWriter()
{
    _objectStack.push(DataValue::Object());
}

void DataValueComponentWriter::beginObject(const char* name)
{
    _objectNameStack.push(name);
    _objectStack.push(DataValue::Object());
}

void DataValueComponentWriter::endObject()
{
    std::string name = _objectNameStack.top();
    _objectNameStack.pop();

    DataValue members = _objectStack.top();
    _objectStack.pop();

    _objectStack.top()[name] = DataValue(members);
}

void DataValueComponentWriter::writeMemberDouble(const char* name, double value)
{
    _objectStack.top()[name] = value;
}

void DataValueComponentWriter::writeMemberString(const char* name, const std::string& value)
{
    _objectStack.top()[name] = value;
}

void DataValueComponentWriter::writeMemberVector2(const char* name, const Vector2<>& value)
{
    _objectStack.top()[name] = value;
}

void DataValueComponentWriter::writeMemberVector3(const char* name, const Vector3<>& value)
{
    _objectStack.top()[name] = value;
}

void DataValueComponentWriter::writeMemberVector4(const char* name, const Vector4<>& value)
{
    _objectStack.top()[name] = value;
}

void DataValueComponentWriter::writeMemberQuaternion(const char* name, const Quaternion<>& value)
{
    _objectStack.top()[name] = value;
}

DataValue DataValueComponentWriter::dataValue() const
{
    return DataValue(_objectStack.top());
}

BinaryComponentWriter::BinaryComponentWriter(WriteStream& stream) :
    _stream(&stream)
{
}

void BinaryComponentWriter::beginObject(const char* name)
{
    name;
}

void BinaryComponentWriter::endObject()
{
}

void BinaryComponentWriter::writeMemberDouble(const char* name, double value)
{
    name;
    _stream->writeDouble(value);
}

void BinaryComponentWriter::writeMemberString(const char* name, const std::string& value)
{
    name;
    _stream->writeString(value);
}

void BinaryComponentWriter::writeMemberVector2(const char* name, const Vector2<>& value)
{
    name;
    _stream->writeVector2(value);
}

void BinaryComponentWriter::writeMemberVector3(const char* name, const Vector3<>& value)
{
    name;
    _stream->writeVector3(value);
}

void BinaryComponentWriter::writeMemberVector4(const char* name, const Vector4<>& value)
{
    name;
    _stream->writeVector4(value);
}

void BinaryComponentWriter::writeMemberQuaternion(const char* name, const Quaternion<>& value)
{
    name;
    _stream->writeQuaternion(value);
}