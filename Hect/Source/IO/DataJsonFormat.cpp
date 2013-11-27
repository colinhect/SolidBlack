#include "Hect.h"

#include <json/json.h>

using namespace hect;

DataValue toDataValue(Json::Value& jsonValue);

DataValue DataJsonFormat::load(const std::string& json)
{
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(json, root))
    {
        throw Error(reader.getFormattedErrorMessages());
    }
    return toDataValue(root);
}

DataValue DataJsonFormat::load(ReadStream& stream)
{
    std::string json = stream.readAllToString();

    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(json, root))
    {
        throw Error(reader.getFormattedErrorMessages());
    }
    return toDataValue(root);
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