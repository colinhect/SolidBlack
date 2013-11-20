#include "Hect.h"

using namespace hect;

ShaderJsonFormat::ShaderJsonFormat()
{
    _paramBindings["None"] = ShaderParamBinding::None;
    _paramBindings["RenderTargetSize"] = ShaderParamBinding::RenderTargetSize;
    _paramBindings["CameraPosition"] = ShaderParamBinding::CameraPosition;
    _paramBindings["CameraUp"] = ShaderParamBinding::CameraUp;
    _paramBindings["ViewMatrix"] = ShaderParamBinding::ViewMatrix;
    _paramBindings["ProjectionMatrix"] = ShaderParamBinding::ProjectionMatrix;
    _paramBindings["ViewProjectionMatrix"] = ShaderParamBinding::ViewProjectionMatrix;
    _paramBindings["ModelMatrix"] = ShaderParamBinding::ModelMatrix;
    _paramBindings["ModelViewMatrix"] = ShaderParamBinding::ModelViewMatrix;
    _paramBindings["ModelViewProjectionMatrix"] = ShaderParamBinding::ModelViewProjectionMatrix;

    _valueTypes["Int"] = ShaderValueType::Int;
    _valueTypes["Float"] = ShaderValueType::Float;
    _valueTypes["Vector2"] = ShaderValueType::Vector2;
    _valueTypes["Vector3"] = ShaderValueType::Vector3;
    _valueTypes["Vector4"] = ShaderValueType::Vector4;
    _valueTypes["Matrix4"] = ShaderValueType::Matrix4;
    _valueTypes["Texture"] = ShaderValueType::Texture;
}

void ShaderJsonFormat::load(Shader& shader, const DataValue& dataValue, AssetCache& assetCache)
{
    ShaderModule::RefArray modules;

    // Add all modules
    for (const DataValue& module : dataValue["modules"])
    {
        AssetHandle<ShaderModule> moduleHandle = assetCache.getHandle<ShaderModule>(module.asString());
        modules.push_back(moduleHandle.getShared());
    }

    ShaderParam::Array params;

    // Add all parameters
    for (std::string& name : dataValue["params"].memberNames())
    {
        params.push_back(_parseParameter(name, dataValue["params"][name]));
    }

    shader = Shader(modules, params);
}

ShaderValue ShaderJsonFormat::parseValue(ShaderValueType type, const DataValue& dataValue) const
{
    switch (type)
    {
    case ShaderValueType::Int:
    case ShaderValueType::Texture:
        return ShaderValue(dataValue.asInt(), type);
    case ShaderValueType::Float:
        return ShaderValue((float)dataValue.asDouble());
    case ShaderValueType::Vector2:
        return ShaderValue(parseVector2(dataValue));
    case ShaderValueType::Vector3:
        return ShaderValue(parseVector3(dataValue));
    case ShaderValueType::Vector4:
        return ShaderValue(parseVector4(dataValue));
    case ShaderValueType::Matrix4:
        return ShaderValue(parseMatrix4(dataValue));
    default:
        return ShaderValue();
    }
}

ShaderParam ShaderJsonFormat::_parseParameter(const std::string& name, const DataValue& dataValue)
{
    if (!dataValue["type"].isNull())
    {
        auto type = _parseValueType(dataValue["type"]);

        const DataValue& value = dataValue["value"];
        if (!value.isNull())
        {
            return ShaderParam(name, parseValue(type, value));
        }
        else
        {
            return ShaderParam(name, type);
        }
    }
    else if (!dataValue["binding"].isNull())
    {
        auto binding = _parseParameterBinding(dataValue["binding"]);
        return ShaderParam(name, binding);
    }
    else
    {
        throw Error("No type or binding specified");
    }
}

ShaderParamBinding ShaderJsonFormat::_parseParameterBinding(const DataValue& dataValue)
{
    auto it = _paramBindings.find(dataValue.asString());
    if (it == _paramBindings.end())
    {
        throw Error(format("Invalid parameter binding '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

ShaderValueType ShaderJsonFormat::_parseValueType(const DataValue& dataValue)
{
    auto it = _valueTypes.find(dataValue.asString());
    if (it == _valueTypes.end())
    {
        throw Error(format("Invalid parameter type '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}