#include "Hect.h"

using namespace hect;

MaterialJsonFormat::MaterialJsonFormat()
{
    _states["Blend"] = RenderState::Blend;
    _states["DepthTest"] = RenderState::DepthTest;
    _states["DepthWrite"] = RenderState::DepthWrite;
    _states["CullFace"] = RenderState::CullFace;

    _blendFactors["Zero"] = BlendFactor::Zero;
    _blendFactors["One"] = BlendFactor::One;
    _blendFactors["SourceColor"] = BlendFactor::SourceColor;
    _blendFactors["OneMinusSourceColor"] = BlendFactor::OneMinusSourceColor;
    _blendFactors["DestColor"] = BlendFactor::DestColor;
    _blendFactors["OneMinusDestColor"] = BlendFactor::OneMinusDestColor;
    _blendFactors["SourceAlpha"] = BlendFactor::SourceAlpha;
    _blendFactors["OneMinusSourceAlpha"] = BlendFactor::OneMinusSourceAlpha;
    _blendFactors["DestAlpha"] = BlendFactor::DestAlpha;
    _blendFactors["OneMinusDestAlpha"] = BlendFactor::OneMinusDestAlpha;
}

void MaterialJsonFormat::load(Material& material, const DataValue& dataValue, AssetCache& assetCache)
{
    ShaderJsonFormat shaderJsonFormat;

    Technique::Array techniques;

    // Base material
    if (dataValue["base"].isString())
    {
        Path basePath = dataValue["base"].asString();
        AssetHandle<Material> handle = assetCache.getHandle<Material>(basePath);
        techniques = handle.get()->techniques(); // Copy the base material techniques
    }

    // Techniques
    size_t techniqueIndex = 0;
    for (const DataValue& techniqueValue : dataValue["techniques"])
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
            ShaderArg::Array shaderArgs;

            if (passIndex < passes.size())
            {
                renderMode = passes[passIndex].renderMode();
                textures = passes[passIndex].textures();
                shader = passes[passIndex].shader();
                shaderArgs = passes[passIndex].shaderArgs();
            }

            // Shader
            if (passValue["shader"].isString())
            {
                Path path = passValue["shader"].asString();
                shader = assetCache.get<Shader>(path);
            }

            // Shader arguments
            const DataValue& shaderArgsValue = passValue["shaderArgs"];
            for (const std::string& name : shaderArgsValue.memberNames())
            {
                if (!shader)
                {
                    throw Error("Cannot have shader arguments without a shader");
                }

                const ShaderParam& param = shader->paramWithName(name);
                ShaderValue value = shaderJsonFormat.parseValue(param.type(), shaderArgsValue[name]);

                bool foundArgument = false;
                for (ShaderArg& arg : shaderArgs)
                {
                    if (arg.paramName() == name)
                    {
                        arg = ShaderArg(name, value);
                        foundArgument = true;
                        break;
                    }
                }

                if (!foundArgument)
                {
                    shaderArgs.push_back(ShaderArg(name, value));
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
                passes.push_back(Pass(renderMode, textures, shader, shaderArgs));
            }

            // Otherwise replace the texture already existing at the index
            else
            {
                passes[passIndex] = Pass(renderMode, textures, shader, shaderArgs);
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

RenderState MaterialJsonFormat::_parseState(const DataValue& dataValue)
{
    auto it = _states.find(dataValue.asString());
    if (it == _states.end())
    {
        throw Error(format("Invalid render state '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

BlendFactor MaterialJsonFormat::_parseBlendFactor(const DataValue& dataValue)
{
    auto it = _blendFactors.find(dataValue.asString());
    if (it == _blendFactors.end())
    {
        throw Error(format("Invalid blend factor '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}