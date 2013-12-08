#pragma once

class RenderingSystem :
    public System
{
public:
    RenderingSystem(Renderer& renderer, AssetCache& assetCache);

    bool includesEntity(const Entity& entity) const;

    void renderAll(Camera& camera, RenderTarget& target);

    double gamma() const;
    void setGamma(double gamma);

    double exposure() const;
    void setExposure(double exposure);

private:
    FrameBuffer _geometryBuffer;
    FrameBuffer _lightBuffer;

    Shader::Ref _ambientLightShader;
    Shader::Ref _directionalLightShader;
    Shader::Ref _compositorShader;
    Mesh::Ref _screenMesh;

    RenderMode _additiveLightMode;

    Renderer* _renderer;

    const Uniform* _ambientLightColorUniform;
    const Uniform* _directionalLightColorUniform;
    const Uniform* _directionalLightDirectionUniform;
    const Uniform* _directionalLightViewUniform;
    const Uniform* _oneOverGammaUniform;
    const Uniform* _exposureUniform;

    double _gamma;
    double _exposure;

    bool _buffersInitialized;
};