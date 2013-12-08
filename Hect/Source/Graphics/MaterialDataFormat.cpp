#include "Hect.h"

using namespace hect;

void MaterialDataFormat::load(Material& material, const std::string& name, const DataValue& dataValue, AssetCache& assetCache)
{
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
            PassUniformValue::Array uniformValues;

            if (passIndex < passes.size())
            {
                renderMode = passes[passIndex].renderMode();
                textures = passes[passIndex].textures();
                shader = passes[passIndex].shader();
                uniformValues = passes[passIndex].uniformValues();
            }

            // Shader
            if (passValue["shader"].isString())
            {
                Path path = passValue["shader"].asString();
                shader = assetCache.get<Shader>(path);
            }

            // Uniform values
            const DataValue& uniformValue = passValue["uniformValues"];
            for (const std::string& name : uniformValue.memberNames())
            {
                if (!shader)
                {
                    throw Error("Cannot have uniform values without a shader");
                }

                const Uniform& uniform = shader->uniformWithName(name);
                UniformValue value = ShaderDataFormat::parseValue(uniform.type(), uniformValue[name]);

                bool foundUniformValue = false;
                for (PassUniformValue& uniformValue : uniformValues)
                {
                    if (uniformValue.uniformName() == name)
                    {
                        uniformValue = PassUniformValue(name, value);
                        foundUniformValue = true;
                        break;
                    }
                }

                if (!foundUniformValue)
                {
                    uniformValues.push_back(PassUniformValue(name, value));
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
                passes.push_back(Pass(renderMode, textures, shader, uniformValues));
            }

            // Otherwise replace the texture already existing at the index
            else
            {
                passes[passIndex] = Pass(renderMode, textures, shader, uniformValues);
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

    material = Material(name, techniques);
}

RenderState MaterialDataFormat::_parseState(const DataValue& dataValue)
{
    static std::map<std::string, RenderState> states;

    if (states.empty())
    {
        states["Blend"] = RenderState::Blend;
        states["DepthTest"] = RenderState::DepthTest;
        states["DepthWrite"] = RenderState::DepthWrite;
        states["CullFace"] = RenderState::CullFace;
    }

    auto it = states.find(dataValue.asString());
    if (it == states.end())
    {
        throw Error(format("Invalid render state '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

BlendFactor MaterialDataFormat::_parseBlendFactor(const DataValue& dataValue)
{
    static std::map<std::string, BlendFactor> blendFactors;

    if (blendFactors.empty())
    {
        blendFactors["Zero"] = BlendFactor::Zero;
        blendFactors["One"] = BlendFactor::One;
        blendFactors["SourceColor"] = BlendFactor::SourceColor;
        blendFactors["OneMinusSourceColor"] = BlendFactor::OneMinusSourceColor;
        blendFactors["DestColor"] = BlendFactor::DestColor;
        blendFactors["OneMinusDestColor"] = BlendFactor::OneMinusDestColor;
        blendFactors["SourceAlpha"] = BlendFactor::SourceAlpha;
        blendFactors["OneMinusSourceAlpha"] = BlendFactor::OneMinusSourceAlpha;
        blendFactors["DestAlpha"] = BlendFactor::DestAlpha;
        blendFactors["OneMinusDestAlpha"] = BlendFactor::OneMinusDestAlpha;
    }

    auto it = blendFactors.find(dataValue.asString());
    if (it == blendFactors.end())
    {
        throw Error(format("Invalid blend factor '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}