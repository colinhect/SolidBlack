#pragma once

#include <Hect.h>
using namespace hect;

class DeferredRenderingSystem :
    public RenderingSystem
{
public:
    DeferredRenderingSystem(AssetCache& assetCache, const DataValue& settings);

    void renderAll(Camera& camera, Gpu& gpu, RenderTarget& target);

    double gamma() const;
    void setGamma(double gamma);

    double exposure() const;
    void setExposure(double exposure);

private:
    std::unique_ptr<FrameBuffer> _frameBuffer;

    Shader::Ref _compositorShader;
    Mesh::Ref _screenMesh;

    const Uniform* _oneOverGammaUniform;
    const Uniform* _exposureUniform;

    double _gamma;
    double _exposure;
};