#pragma once

class RenderingSystem :
    public System
{
public:
    RenderingSystem(Renderer& renderer, AssetCache& assetCache);

    void addEntity(Entity& entity);
    void removeEntity(Entity& entity);

    void renderAll(Camera& camera, RenderTarget& target);

    double gamma() const;
    void setGamma(double gamma);

    double exposure() const;
    void setExposure(double exposure);

private:
    void _renderMeshPass(const Camera& camera, const RenderTarget& target, const Pass& pass, Mesh& mesh, const Transform& transform);
    void _initializeBuffers(unsigned width, unsigned height);

    std::vector<Geometry*> _geometryComponents;
    std::vector<Transform*> _transformComponents;
    std::vector<AmbientLight*> _ambientLightComponents;
    std::vector<DirectionalLight*> _directionalLightComponents;

    FrameBuffer _geometryBuffer;
    FrameBuffer _lightingBuffer;

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