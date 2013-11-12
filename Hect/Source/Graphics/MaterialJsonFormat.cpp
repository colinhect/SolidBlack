#include "Hect.h"

using namespace hect;

MaterialJsonFormat::MaterialJsonFormat()
{
    _states["Blend"] = RenderMode::Blend;
    _states["DepthTest"] = RenderMode::DepthTest;
    _states["DepthWrite"] = RenderMode::DepthWrite;
    _states["CullFace"] = RenderMode::CullFace;

    _blendFactors["Zero"] = RenderMode::Zero;
    _blendFactors["One"] = RenderMode::One;
    _blendFactors["SourceColor"] = RenderMode::SourceColor;
    _blendFactors["OneMinusSourceColor"] = RenderMode::OneMinusSourceColor;
    _blendFactors["DestColor"] = RenderMode::DestColor;
    _blendFactors["OneMinusDestColor"] = RenderMode::OneMinusDestColor;
    _blendFactors["SourceAlpha"] = RenderMode::SourceAlpha;
    _blendFactors["OneMinusSourceAlpha"] = RenderMode::OneMinusSourceAlpha;
    _blendFactors["DestAlpha"] = RenderMode::DestAlpha;
    _blendFactors["OneMinusDestAlpha"] = RenderMode::OneMinusDestAlpha;
}

void MaterialJsonFormat::load(Material& material, ReadStream& stream, AssetCache& assetCache)
{
    ShaderJsonFormat shaderJsonFormat;
    DataValue root = JsonParser().parse(stream);

    Technique::Array techniques;

    // Base material
    if (root["base"].isString())
    {
        Path basePath = root["base"].asString();
        AssetHandle<Material> handle = assetCache.getHandle<Material>(basePath);
        techniques = handle.get()->techniques(); // Copy the base material techniques
    }

    // Techniques
    size_t techniqueIndex = 0;
    for (const DataValue& techniqueValue : root["techniques"])
    {
        Pass::Array passes;
        if (techniqueIndex < techniques.size())
        {
            passes = techniques[techniqueIndex].passes();
        }

        // Passes
        size_t passIndex = 0;
        for (const DataValue& passValue : techniqueValue)
        {
            RenderMode renderMode;
            Texture::RefArray textures;
            Shader::Ref shader;
            Shader::Argument::Array shaderArguments;

            if (passIndex < passes.size())
            {
                renderMode = passes[passIndex].renderMode();
                textures = passes[passIndex].textures();
                shader = passes[passIndex].shader();
                shaderArguments = passes[passIndex].shaderArguments();
            }

            // Shader
            if (passValue["shader"].isString())
            {
                Path path = passValue["shader"].asString();
                shader = assetCache.get<Shader>(path);
            }

            // Shader arguments
            const DataValue& shaderArgumentsValue = passValue["shaderArguments"];
            for (const std::string& name : shaderArgumentsValue.memberNames())
            {
                if (!shader)
                {
                    throw Error("Cannot have shader arguments without a shader");
                }

                const Shader::Parameter& parameter = shader->parameterWithName(name);
                Shader::Value value = shaderJsonFormat.parseValue(parameter.type(), shaderArgumentsValue[name]);

                bool foundArgument = false;
                for (Shader::Argument& argument : shaderArguments)
                {
                    if (argument.parameterName() == name)
                    {
                        argument = Shader::Argument(name, value);
                        foundArgument = true;
                        break;
                    }
                }

                if (!foundArgument)
                {
                    shaderArguments.push_back(Shader::Argument(name, value));
                }
            }

            // Textures
            size_t textureIndex = 0;
            for (const DataValue& textureValue : passValue["textures"])
            {
                if (!textureValue.isString())
                {
                    continue;
                }

                Path path = textureValue.asString();
                Texture::Ref texture = assetCache.get<Texture>(path);

                // Append a new texture if needed
                if (textureIndex >= textures.size())
                {
                    textures.push_back(texture);
                }

                // Otherwise replace the texture already existing at the index
                else
                {
                    textures[textureIndex] = texture;
                }

                ++textureIndex;
            }

            // Render mode
            const DataValue& renderModeValue = passValue["renderMode"];
            if (renderModeValue.isObject())
            {
                // Enabled states
                for (const DataValue& stateValue : renderModeValue["enabledStates"])
                {
                    renderMode.enableState(_parseState(stateValue));
                }

                // Disabled states
                for (const DataValue& stateValue : renderModeValue["disabledStates"])
                {
                    renderMode.disableState(_parseState(stateValue));
                }

                // Blend factors
                const DataValue& blendFactorValues = renderModeValue["blendFactors"];
                if (blendFactorValues.isArray() && blendFactorValues.size() == 2)
                {
                    auto sourceFactor = _parseBlendFactor(blendFactorValues[0]);
                    auto destFactor = _parseBlendFactor(blendFactorValues[1]);
                    renderMode.setBlendFactors(sourceFactor, destFactor);
                }
            }

            // Append a new texture if needed
            if (passIndex >= passes.size())
            {
                passes.push_back(Pass(renderMode, textures, shader, shaderArguments));
            }

            // Otherwise replace the texture already existing at the index
            else
            {
                passes[passIndex] = Pass(renderMode, textures, shader, shaderArguments);
            }

            ++passIndex;
        }

        if (techniqueIndex < techniques.size())
        {
            techniques[techniqueIndex] = Technique(passes);
        }
        else
        {
            techniques.push_back(Technique(passes));
        }

        ++techniqueIndex;
    }

    material = Material(techniques);
}

RenderMode::State MaterialJsonFormat::_parseState(const DataValue& dataValue)
{
    auto it = _states.find(dataValue.asString());
    if (it == _states.end())
    {
        throw Error(format("Invalid render state '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

RenderMode::BlendFactor MaterialJsonFormat::_parseBlendFactor(const DataValue& dataValue)
{
    auto it = _blendFactors.find(dataValue.asString());
    if (it == _blendFactors.end())
    {
        throw Error(format("Invalid blend factor '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}