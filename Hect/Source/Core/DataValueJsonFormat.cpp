#include "Hect.h"

#include <json/json.h>

using namespace hect;

DataValue toDataValue(Json::Value& jsonValue);
Json::Value fromDataValue(const DataValue& dataValue);

void DataValueJsonFormat::save(const DataValue& dataValue, std::string& json)
{
    Json::Value jsonValue = fromDataValue(dataValue);
    json = jsonValue.toStyledString();
}

void DataValueJsonFormat::save(const DataValue& dataValue, WriteStream& stream)
{
    std::string json;
    DataValueJsonFormat::save(dataValue, json);
    stream.writeString(json, false);
}

void DataValueJsonFormat::load(DataValue& dataValue, const std::string& json)
{
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(json, root))
    {
        throw Error(reader.getFormattedErrorMessages());
    }
    dataValue = toDataValue(root);
}

void DataValueJsonFormat::load(DataValue& dataValue, ReadStream& stream)
{
    std::string json = stream.readAllToString();
    load(dataValue, json);
}

DataValue toDataValue(Json::Value& jsonValue)
{
    if (jsonValue.isBool())
    {
        return DataValue(jsonValue.asBool());
    }
    else if (jsonValue.isNumeric())
    {
        return DataValue(jsonValue.asDouble());
    }
    else if (jsonValue.isString())
    {
        return DataValue(jsonValue.asString());
    }
    else if (jsonValue.isArray())
    {
        auto elements = DataValue::Array();
        for (Json::Value& element : jsonValue)
        {
            elements.push_back(toDataValue(element));
        }
        return DataValue(elements);
    }
    else if (jsonValue.isObject())
    {
        auto members = DataValue::Object();
        for (std::string& name : jsonValue.getMemberNames())
        {
            members[name] = toDataValue(jsonValue[name]);
        }
        return DataValue(members);
    }

    return DataValue();
}

Json::Value fromDataValue(const DataValue& dataValue)
{
    if (dataValue.isBool())
    {
        return Json::Value(dataValue.asBool());
    }
    else if (dataValue.isNumber())
    {
        return Json::Value(dataValue.asDouble());
    }
    else if (dataValue.isString())
    {
        return Json::Value(dataValue.asString());
    }
    else if (dataValue.isArray())
    {
        Json::Value jsonValue(Json::arrayValue);
        for (const DataValue& element : dataValue)
        {
            jsonValue.append(fromDataValue(element));
        }
        return jsonValue;
    }
    else if (dataValue.isObject())
    {
        Json::Value jsonValue(Json::objectValue);
        for (const std::string& name : dataValue.memberNames())
        {
            jsonValue[name] = fromDataValue(dataValue[name]);
        }
        return jsonValue;
    }

    return Json::Value();
}