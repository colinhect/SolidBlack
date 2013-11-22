#include "SolidBlackScene.h"

SolidBlackScene::SolidBlackScene(AssetCache& assetCache) :
    Scene(128),
    _hdrCompositorShader(assetCache.get<Shader>("Shaders/HdrCompositor.shader")),
    _screenMesh(assetCache.get<Mesh>("Meshes/Screen.mesh")),
    _oneOverGammaUniform(&_hdrCompositorShader->uniformWithName("oneOverGamma")),
    _exposureUniform(&_hdrCompositorShader->uniformWithName("exposure")),
    _gamma(2.2),
    _exposure(0.025)
{

    addSystem(_cameraSystem);
    addSystem(_renderingSystem);
    addSystem(_debugRenderingSystem);
}

SolidBlackScene::~SolidBlackScene()
{
    removeSystem(_debugRenderingSystem);
    removeSystem(_renderingSystem);
    removeSystem(_cameraSystem);
}

void SolidBlackScene::update(double timeStep)
{
    _cameraSystem.update();
    refresh();
}

void SolidBlackScene::render(Gpu& gpu, RenderTarget& target)
{
    if (!_cameraSystem.hasCamera())
    {
        return;
    }

    if (!_frameBuffer)
    {
        Texture::Array targets;
        targets.push_back(Texture(target.width(), target.height(), PixelType::Half, PixelFormat::Rgb, TextureFilter::Nearest, TextureFilter::Nearest, false, false));
        _frameBuffer.reset(new FrameBuffer(targets));
    }

    Camera& camera = _cameraSystem.camera();

    // Render scene to floating point frame buffer
    gpu.beginFrame();
    gpu.bindTarget(*_frameBuffer);
    gpu.clear();
    _renderingSystem.renderAll(camera, gpu, *_frameBuffer);
    gpu.endFrame();

    // Render the tonemapped frame buffer
    gpu.beginFrame();
    gpu.bindTarget(target);
    gpu.clear();

    gpu.bindShader(*_hdrCompositorShader);
    gpu.setUniform(*_oneOverGammaUniform, 1.0f / (float)_gamma);
    gpu.setUniform(*_exposureUniform, (float)_exposure);
    gpu.bindTexture(_frameBuffer->targets()[0], 0);
    gpu.bindMesh(*_screenMesh);
    gpu.draw();

    // Draw debug info
    //_debugRenderingSystem.renderAll(camera, gpu);

    gpu.endFrame();
}

double SolidBlackScene::gamma() const
{
    return _gamma;
}

void SolidBlackScene::setGamma(double gamma)
{
    _gamma = gamma;
    LOG_DEBUG(format("Gamma: %f", gamma));
}

void SolidBlackScene::setExposure(double exposure)
{
    _exposure = exposure;
    LOG_DEBUG(format("Exposure: %f", exposure));
}

double SolidBlackScene::exposure() const
{
    return _exposure;
}