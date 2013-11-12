#include "Hect.h"

using namespace hect;

ShaderJsonFormat::ShaderJsonFormat()
{
    _parameterBindings["None"] = Shader::Parameter::None;
    _parameterBindings["RenderTargetSize"] = Shader::Parameter::RenderTargetSize;
    _parameterBindings["CameraPosition"] = Shader::Parameter::CameraPosition;
    _parameterBindings["CameraUp"] = Shader::Parameter::CameraUp;
    _parameterBindings["ViewMatrix"] = Shader::Parameter::ViewMatrix;
    _parameterBindings["ProjectionMatrix"] = Shader::Parameter::ProjectionMatrix;
    _parameterBindings["ViewProjectionMatrix"] = Shader::Parameter::ViewProjectionMatrix;
    _parameterBindings["ModelMatrix"] = Shader::Parameter::ModelMatrix;
    _parameterBindings["ModelViewMatrix"] = Shader::Parameter::ModelViewMatrix;
    _parameterBindings["ModelViewProjectionMatrix"] = Shader::Parameter::ModelViewProjectionMatrix;

    _valueTypes["Int"] = Shader::Value::Int;
    _valueTypes["Float"] = Shader::Value::Float;
    _valueTypes["Vector2"] = Shader::Value::Vector2;
    _valueTypes["Vector3"] = Shader::Value::Vector3;
    _valueTypes["Vector4"] = Shader::Value::Vector4;
    _valueTypes["Matrix4"] = Shader::Value::Matrix4;
    _valueTypes["Texture"] = Shader::Value::Texture;
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

    Shader::Parameter::Array parameters;

    // Add all parameters
    for (std::string& name : dataValue["parameters"].memberNames())
    {
        parameters.push_back(_parseParameter(name, dataValue["parameters"][name]));
    }

    shader = Shader(modules, parameters);
}

Shader::Value ShaderJsonFormat::parseValue(Shader::Value::Type type, const DataValue& dataValue) const
{
    switch (type)
    {
    case Shader::Value::Int:
    case Shader::Value::Texture:
        return Shader::Value(dataValue.asInt(), type);
    case Shader::Value::Float:
        return Shader::Value((float)dataValue.asDouble());
    case Shader::Value::Vector2:
        return Shader::Value(parseVector2(dataValue));
    case Shader::Value::Vector3:
        return Shader::Value(parseVector3(dataValue));
    case Shader::Value::Vector4:
        return Shader::Value(parseVector4(dataValue));
    case Shader::Value::Matrix4:
        return Shader::Value(parseMatrix4(dataValue));
    default:
        return Shader::Value();
    }
}

Shader::Parameter ShaderJsonFormat::_parseParameter(const std::string& name, const DataValue& dataValue)
{
    if (!dataValue["type"].isNull())
    {
        auto type = _parseValueType(dataValue["type"]);

        const DataValue& value = dataValue["value"];
        if (!value.isNull())
        {
            return Shader::Parameter(name, parseValue(type, value));
        }
        else
        {
            return Shader::Parameter(name, type);
        }
    }
    else if (!dataValue["binding"].isNull())
    {
        auto binding = _parseParameterBinding(dataValue["binding"]);
        return Shader::Parameter(name, binding);
    }
    else
    {
        throw Error("No type or binding specified");
    }
}

Shader::Parameter::Binding ShaderJsonFormat::_parseParameterBinding(const DataValue& dataValue)
{
    auto it = _parameterBindings.find(dataValue.asString());
    if (it == _parameterBindings.end())
    {
        throw Error(format("Invalid parameter binding '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

Shader::Value::Type ShaderJsonFormat::_parseValueType(const DataValue& dataValue)
{
    auto it = _valueTypes.find(dataValue.asString());
    if (it == _valueTypes.end())
    {
        throw Error(format("Invalid parameter type '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}