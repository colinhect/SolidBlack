#include "Hect.h"

using namespace hect;

const DataValue DataValue::_null;
const DataValue::Array DataValue::_emptyArray;
const std::string DataValue::_emptyString;

DataValue::DataValue() :
    _type(DataValueType::Null)
{
}

DataValue::DataValue(bool value) :
    _type(DataValueType::Bool),
    _data(value)
{
}

DataValue::DataValue(int value) :
    _type(DataValueType::Number),
    _data((double)value)
{
}

DataValue::DataValue(unsigned value) :
    _type(DataValueType::Number),
    _data((double)value)
{
}

DataValue::DataValue(double value) :
    _type(DataValueType::Number),
    _data(value)
{
}

DataValue::DataValue(const Vector2<>& value) :
    _type(DataValueType::Array)
{
    Array array;
    array.push_back(value.x);
    array.push_back(value.y);
    _data = array;
}

DataValue::DataValue(const Vector3<>& value) :
    _type(DataValueType::Array)
{
    Array array;
    array.push_back(value.x);
    array.push_back(value.y);
    array.push_back(value.z);
    _data = array;
}

DataValue::DataValue(const Vector4<>& value) :
    _type(DataValueType::Array)
{
    Array array;
    array.push_back(value.x);
    array.push_back(value.y);
    array.push_back(value.z);
    array.push_back(value.w);
    _data = array;
}

DataValue::DataValue(const Matrix4<>& value) :
    _type(DataValueType::Array)
{
    Array array;
    for (unsigned i = 0; i < 16; ++i)
    {
        _data.as<Array>().push_back(value[i]);
    }
    _data = array;
}

DataValue::DataValue(const Quaternion<>& value) :
    _type(DataValueType::Array)
{
    Array array;
    array.push_back(value.x);
    array.push_back(value.y);
    array.push_back(value.z);
    array.push_back(value.w);
    _data = array;
}

DataValue::DataValue(const char* value) :
    _type(DataValueType::String),
    _data(std::string(value))
{
}

DataValue::DataValue(const std::string& value) :
    _type(DataValueType::String),
    _data(value)
{
}

DataValue::DataValue(const Array& elements) :
    _type(DataValueType::Array),
    _data(elements)
{
}

DataValue::DataValue(const Object& members) :
    _type(DataValueType::Object),
    _data(members)
{
}

DataValue::DataValue(DataValue&& dataValue) :
    _type(dataValue._type),
    _data(std::move(dataValue._data))
{
    dataValue._type = DataValueType::Null;
}

DataValueType DataValue::type() const
{
    return _type;
}

const DataValue& DataValue::or(const DataValue& dataValue) const
{
    if (isNull())
    {
        return dataValue;
    }
    else
    {
        return *this;
    }
}

bool DataValue::isNull() const
{
    return _type == DataValueType::Null;
}

bool DataValue::isBool() const
{
    return _type == DataValueType::Bool;
}

bool DataValue::isNumber() const
{
    return _type == DataValueType::Number;
}

bool DataValue::isString() const
{
    return _type == DataValueType::String;
}

bool DataValue::isArray() const
{
    return _type == DataValueType::Array;
}

bool DataValue::isObject() const
{
    return _type == DataValueType::Object;
}

bool DataValue::asBool() const
{
    if (isBool())
    {
        return _data.as<bool>();
    }
    else
    {
        return false;
    }
}

int DataValue::asInt() const
{
    if (isNumber())
    {
        return (int)_data.as<double>();
    }
    else
    {
        return 0;
    }
}

unsigned DataValue::asUnsigned() const
{
    if (isNumber())
    {
        return (unsigned)_data.as<double>();
    }
    else
    {
        return 0;
    }
}

double DataValue::asDouble() const
{
    if (isNumber())
    {
        return _data.as<double>();
    }
    else
    {
        return 0.0;
    }
}

Vector2<> DataValue::asVector2() const
{
    Vector2<> result;

    size_t i = 0;
    for (const DataValue& component : *this)
    {
        if (i < 2)
        {
            result[i++] = component.asDouble();
        }
        else
        {
            break;
        }
    }

    return result;
}

Vector3<> DataValue::asVector3() const
{
    Vector3<> result;

    size_t i = 0;
    for (const DataValue& component : *this)
    {
        if (i < 3)
        {
            result[i++] = component.asDouble();
        }
        else
        {
            break;
        }
    }

    return result;
}

Vector4<> DataValue::asVector4() const
{
    Vector4<> result;

    size_t i = 0;
    for (const DataValue& component : *this)
    {
        if (i < 4)
        {
            result[i++] = component.asDouble();
        }
        else
        {
            break;
        }
    }

    return result;
}

Matrix4<> DataValue::asMatrix4() const
{
    Matrix4<> result;

    size_t i = 0;
    for (const DataValue& component : *this)
    {
        if (i < 16)
        {
            result[i++] = component.asDouble();
        }
        else
        {
            break;
        }
    }

    return result;
}

Quaternion<> DataValue::asQuaternion() const
{
    Quaternion<> result;

    size_t i = 0;
    for (const DataValue& component : *this)
    {
        if (i < 4)
        {
            result[i++] = component.asDouble();
        }
        else
        {
            break;
        }
    }

    return result;
}

const std::string& DataValue::asString() const
{
    if (isString())
    {
        return _data.as<std::string>();
    }
    else
    {
        return _emptyString;
    }
}

size_t DataValue::size() const
{
    if (isArray())
    {
        return _data.as<Array>().size();
    }
    else if (isObject())
    {
        return _data.as<Object>().size();
    }

    return 0;
}

std::vector<std::string> DataValue::memberNames() const
{
    if (isObject())
    {
        std::vector<std::string> result;
        Object& object = _data.as<Object>();
        for (auto& pair : object)
        {
            result.push_back(pair.first);
        }
        return result;
    }
    else
    {
        return std::vector<std::string>();
    }
}

const DataValue& DataValue::operator[](size_t index) const
{
    if (isArray())
    {
        Array& array = _data.as<Array>();
        if (index < array.size())
        {
            return array[index];
        }
        else
        {
            return _null;
        }
    }
    else
    {
        return _null;
    }
}

const DataValue& DataValue::operator[](const std::string& name) const
{
    if (isObject())
    {
        return _data.as<Object>()[name];
    }
    else
    {
        return _null;
    }
}

DataValue::Array::const_iterator DataValue::begin() const
{
    if (isArray())
    {
        return _data.as<Array>().begin();
    }
    else
    {
        return _emptyArray.begin();
    }
}

DataValue::Array::const_iterator DataValue::end() const
{
    if (isArray())
    {
        return _data.as<Array>().end();
    }
    else
    {
        return _emptyArray.end();
    }
}