#include "Hect.h"

using namespace hect;

const DataValue DataValue::_null;
const DataValue::ArrayType DataValue::_emptyArray;
const std::string DataValue::_emptyString;

DataValue::DataValue() :
    _type(Null)
{
}

DataValue::DataValue(bool value) :
    _type(Bool),
    _data(value)
{
}

DataValue::DataValue(int value) :
    _type(Number),
    _data((double)value)
{
}

DataValue::DataValue(unsigned value) :
    _type(Number),
    _data((double)value)
{
}

DataValue::DataValue(double value) :
    _type(Number),
    _data(value)
{
}

DataValue::DataValue(const char* value) :
    _type(String),
    _data(std::string(value))
{
}

DataValue::DataValue(const std::string& value) :
    _type(String),
    _data(value)
{
}

DataValue::DataValue(const ArrayType& elements) :
    _type(Array),
    _data(elements)
{
}

DataValue::DataValue(const ObjectType& members) :
    _type(Object),
    _data(members)
{
}

DataValue::DataValue(DataValue&& dataValue) :
    _type(dataValue._type),
    _data(std::move(dataValue._data))
{
    dataValue._type = Null;
}

DataValue::Type DataValue::type() const
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
    return _type == Null;
}

bool DataValue::isBool() const
{
    return _type == Bool;
}

bool DataValue::isNumber() const
{
    return _type == Number;
}

bool DataValue::isString() const
{
    return _type == String;
}

bool DataValue::isArray() const
{
    return _type == Array;
}

bool DataValue::isObject() const
{
    return _type == Object;
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
        return _data.as<ArrayType>().size();
    }
    else if (isObject())
    {
        return _data.as<ObjectType>().size();
    }

    return 0;
}

std::vector<std::string> DataValue::memberNames() const
{
    if (isObject())
    {
        std::vector<std::string> result;
        ObjectType& object = _data.as<ObjectType>();
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
        return _data.as<ArrayType>()[index];
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
        return _data.as<ObjectType>()[name];
    }
    else
    {
        return _null;
    }
}

DataValue::ArrayType::const_iterator DataValue::begin() const
{
    if (isArray())
    {
        return _data.as<ArrayType>().begin();
    }
    else
    {
        return _emptyArray.begin();
    }
}

DataValue::ArrayType::const_iterator DataValue::end() const
{
    if (isArray())
    {
        return _data.as<ArrayType>().end();
    }
    else
    {
        return _emptyArray.end();
    }
}