#include "Hect.h"

using namespace hect;

DataValueReader::DataValueReader(const DataValue& dataValue) :
    _elementIndex(0)
{
    _valueStack.push(dataValue);
}

bool DataValueReader::beginObject()
{
    DataValue& top = _valueStack.top();
    if (!top.isArray())
    {
        throw Error("Cannot begin an unnamed object when the current value is an object");
    }

    if (_elementIndex >= top.size())
    {
        return false;
    }

    _valueStack.push(_read());
    return true;
}

bool DataValueReader::beginObject(const char* name)
{
    DataValue& top = _valueStack.top();
    if (!top.isObject())
    {
        throw Error("Cannot begin a named object when the current value is an array");
    }

    const DataValue& value = top[name];
    if (!value.isNull())
    {
        _valueStack.push(value);
        return true;
    }
    else
    {
        return false;
    }
}

void DataValueReader::endObject()
{
    DataValue top = _valueStack.top();
    if (!top.isObject())
    {
        throw Error("Current value is not an object");
    }

    _valueStack.pop();
}

bool DataValueReader::beginArray(const char* name)
{
    DataValue& top = _valueStack.top();
    if (!top.isObject())
    {
        throw Error("Cannot begin a named array when the current value is an array");
    }

    const DataValue& value = top[name];
    if (!value.isNull())
    {
        _elementIndex = 0;
        _valueStack.push(value);
        return true;
    }
    else
    {
        return false;
    }
}

bool DataValueReader::endArray()
{
    const DataValue& top = _valueStack.top();
    if (!top.isArray())
    {
        throw Error("Current value is not an array");
    }

    if (_elementIndex >= top.size())
    {
        _valueStack.pop();
        return true;
    }
    return false;
}

bool DataValueReader::hasMember(const char* name)
{
    return !_valueStack.top()[name].isNull();
}

double DataValueReader::readDouble()
{
    return _read().asDouble();
}

double DataValueReader::readDouble(const char* name)
{
    return _read(name).asDouble();
}

std::string DataValueReader::readString()
{
    return _read().asString();
}

std::string DataValueReader::readString(const char* name)
{
    return _read(name).asString();
}

Vector2<> DataValueReader::readVector2()
{
    return _read().asVector2();
}

Vector2<> DataValueReader::readVector2(const char* name)
{
    return _read(name).asVector2();
}

Vector3<> DataValueReader::readVector3()
{
    return _read().asVector3();
}

Vector3<> DataValueReader::readVector3(const char* name)
{
    return _read(name).asVector3();
}

Vector4<> DataValueReader::readVector4()
{
    return _read().asVector4();
}

Vector4<> DataValueReader::readVector4(const char* name)
{
    return _read(name).asVector4();
}

const DataValue& DataValueReader::_read()
{
    DataValue& top = _valueStack.top();
    if (!top.isArray())
    {
        throw Error("Current value is not an array");
    }

    if (_elementIndex >= top.size())
    {
        throw Error("Attempt to read past the end of an array");
    }

    return top[_elementIndex++];
}

const DataValue& DataValueReader::_read(const char* name)
{
    DataValue& top = _valueStack.top();
    if (!top.isObject())
    {
        throw Error("Current value is not an object");
    }

    return top[name];
}

BinaryDataReader::BinaryDataReader(ReadStream& stream) :
    _elementIndex(0),
    _elementCount(0),
    _stream(&stream)
{
}

bool BinaryDataReader::beginObject()
{
    ++_elementIndex;
    return true;
}

bool BinaryDataReader::beginObject(const char* name)
{
    name;
    return true;
}

void BinaryDataReader::endObject()
{
}

bool BinaryDataReader::beginArray(const char* name)
{
    name;
    _elementCount = _stream->readUnsignedInt();
    _elementIndex = 0;
    return true;
}

bool BinaryDataReader::endArray()
{
    return _elementIndex >= _elementCount;
}

bool BinaryDataReader::hasMember(const char* name)
{
    name;
    return true; // Assume that all values are written
}

double BinaryDataReader::readDouble()
{
    ++_elementIndex;
    return _stream->readDouble();
}

double BinaryDataReader::readDouble(const char* name)
{
    name;
    return _stream->readDouble();
}

std::string BinaryDataReader::readString()
{
    ++_elementIndex;
    return _stream->readString();
}

std::string BinaryDataReader::readString(const char* name)
{
    name;
    return _stream->readString();
}

Vector2<> BinaryDataReader::readVector2()
{
    ++_elementIndex;
    return _stream->readVector2();
}

Vector2<> BinaryDataReader::readVector2(const char* name)
{
    name;
    return _stream->readVector2();
}

Vector3<> BinaryDataReader::readVector3()
{
    ++_elementIndex;
    return _stream->readVector3();
}

Vector3<> BinaryDataReader::readVector3(const char* name)
{
    name;
    return _stream->readVector3();
}

Vector4<> BinaryDataReader::readVector4()
{
    ++_elementIndex;
    return _stream->readVector4();
}

Vector4<> BinaryDataReader::readVector4(const char* name)
{
    name;
    return _stream->readVector4();
}