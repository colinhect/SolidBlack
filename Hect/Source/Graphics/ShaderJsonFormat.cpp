#include "Hect.h"

using namespace hect;

ShaderJsonFormat::ShaderJsonFormat()
{
    _uniformBindings["None"] = UniformBinding::None;
    _uniformBindings["RenderTargetSize"] = UniformBinding::RenderTargetSize;
    _uniformBindings["CameraPosition"] = UniformBinding::CameraPosition;
    _uniformBindings["CameraUp"] = UniformBinding::CameraUp;
    _uniformBindings["ViewMatrix"] = UniformBinding::ViewMatrix;
    _uniformBindings["ProjectionMatrix"] = UniformBinding::ProjectionMatrix;
    _uniformBindings["ViewProjectionMatrix"] = UniformBinding::ViewProjectionMatrix;
    _uniformBindings["ModelMatrix"] = UniformBinding::ModelMatrix;
    _uniformBindings["ModelViewMatrix"] = UniformBinding::ModelViewMatrix;
    _uniformBindings["ModelViewProjectionMatrix"] = UniformBinding::ModelViewProjectionMatrix;

    _valueTypes["Int"] = UniformType::Int;
    _valueTypes["Float"] = UniformType::Float;
    _valueTypes["Vector2"] = UniformType::Vector2;
    _valueTypes["Vector3"] = UniformType::Vector3;
    _valueTypes["Vector4"] = UniformType::Vector4;
    _valueTypes["Matrix4"] = UniformType::Matrix4;
    _valueTypes["Texture"] = UniformType::Texture;
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

    Uniform::Array uniforms;

    // Add all uniforms
    for (std::string& name : dataValue["uniforms"].memberNames())
    {
        uniforms.push_back(_parseUniform(name, dataValue["uniforms"][name]));
    }

    shader = Shader(modules, uniforms);
}

UniformValue ShaderJsonFormat::parseValue(UniformType type, const DataValue& dataValue) const
{
    switch (type)
    {
    case UniformType::Int:
    case UniformType::Texture:
        return UniformValue(dataValue.asInt(), type);
    case UniformType::Float:
        return UniformValue((float)dataValue.asDouble());
    case UniformType::Vector2:
        return UniformValue(dataValue.asVector2());
    case UniformType::Vector3:
        return UniformValue(dataValue.asVector3());
    case UniformType::Vector4:
        return UniformValue(dataValue.asVector4());
    case UniformType::Matrix4:
        return UniformValue(dataValue.asMatrix4());
    default:
        return UniformValue();
    }
}

Uniform ShaderJsonFormat::_parseUniform(const std::string& name, const DataValue& dataValue)
{
    if (!dataValue["type"].isNull())
    {
        auto type = _parseType(dataValue["type"]);

        const DataValue& defaultValue = dataValue["defaultValue"];
        if (!defaultValue.isNull())
        {
            return Uniform(name, parseValue(type, defaultValue));
        }
        else
        {
            return Uniform(name, type);
        }
    }
    else if (!dataValue["binding"].isNull())
    {
        auto binding = _parseUniformBinding(dataValue["binding"]);
        return Uniform(name, binding);
    }
    else
    {
        throw Error("No type or binding specified");
    }
}

UniformBinding ShaderJsonFormat::_parseUniformBinding(const DataValue& dataValue)
{
    auto it = _uniformBindings.find(dataValue.asString());
    if (it == _uniformBindings.end())
    {
        throw Error(format("Invalid uniform binding '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

UniformType ShaderJsonFormat::_parseType(const DataValue& dataValue)
{
    auto it = _valueTypes.find(dataValue.asString());
    if (it == _valueTypes.end())
    {
        throw Error(format("Invalid uniform type '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}