#pragma once

#include <Hect.h>
using namespace hect;

class SolidBlackScene :
    public Scene
{
public:
    SolidBlackScene(AssetCache& assetCache);
    ~SolidBlackScene();

    void update(double timeStep);
    void render(Gpu& gpu, RenderTarget& target);

    double gamma() const;
    void setGamma(double gamma);

    double exposure() const;
    void setExposure(double exposure);

private:
    CameraSystem _cameraSystem;
    RenderingSystem _renderingSystem;
    DebugRenderingSystem _debugRenderingSystem;

    std::unique_ptr<FrameBuffer> _frameBuffer;

    Shader::Ref _hdrCompositorShader;
    Mesh::Ref _screenMesh;

    const Uniform* _oneOverGammaUniform;
    const Uniform* _exposureUniform;

    double _gamma;
    double _exposure;
};