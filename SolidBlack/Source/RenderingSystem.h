#pragma once

#include <Hect.h>
using namespace hect;

class RenderingSystem :
    public System
{
public:
    RenderingSystem(Renderer& renderer, AssetCache& assetCache, const DataValue& settings);

    void addEntity(Entity& entity);
    void removeEntity(Entity& entity);

    void renderAll(Camera& camera, RenderTarget& target);

    double gamma() const;
    void setGamma(double gamma);

    double exposure() const;
    void setExposure(double exposure);

private:    
    FrameBuffer _geometryBuffer;
    FrameBuffer _lightBuffer;

    Shader::Ref _compositorShader;
    Mesh::Ref _windowMesh;

    Renderer* _renderer;

    const Uniform* _oneOverGammaUniform;
    const Uniform* _exposureUniform;

    double _gamma;
    double _exposure;

    bool _buffersInitialized;
};