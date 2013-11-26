#include "DeferredRenderingSystem.h"

DeferredRenderingSystem::DeferredRenderingSystem(AssetCache& assetCache, const DataValue& settings) :
    _oneOverGammaUniform(nullptr),
    _exposureUniform(nullptr),
    _gamma(2.2),
    _exposure(0.025)
{
    LOG_INFO("Initializing deferred rendering system...");

    // Load compositor shader
    std::string compositorShaderPath = settings["graphics"]["compositorShader"].asString();
    LOG_INFO(format("Using compositor shader: '%s'", compositorShaderPath.c_str()));
    _compositorShader = assetCache.get<Shader>(compositorShaderPath);
    LOG_INFO("Using compositor shader uniform: 'oneOverGamma'");
    _oneOverGammaUniform = &_compositorShader->uniformWithName("oneOverGamma");
    LOG_INFO("Using compositor shader uniform: 'exposure'");
    _exposureUniform = &_compositorShader->uniformWithName("exposure");
    
    // Load window mesh
    std::string windowMeshPath = settings["graphics"]["windowMesh"].asString();
    LOG_INFO(format("Using window mesh: '%s'", windowMeshPath.c_str()));
    _windowMesh = assetCache.get<Mesh>(windowMeshPath);

    LOG_INFO("Done");
}

void DeferredRenderingSystem::renderAll(Camera& camera, Renderer& renderer, RenderTarget& target)
{
    if (!_frameBuffer || _frameBuffer->width() != target.width() || _frameBuffer->height() != target.height())
    {
        Texture::Array targets;
        targets.push_back(Texture(target.width(), target.height(), PixelType::Half, PixelFormat::Rgb, TextureFilter::Nearest, TextureFilter::Nearest, false, false));
        _frameBuffer.reset(new FrameBuffer(targets));
    }

    // Render scene to floating point frame buffer
    renderer.beginFrame();
    renderer.bindTarget(*_frameBuffer);
    renderer.clear();
    RenderingSystem::renderAll(camera, renderer, *_frameBuffer);
    renderer.endFrame();

    // Render the tonemapped frame buffer
    renderer.beginFrame();
    renderer.bindTarget(target);
    renderer.clear();

    renderer.bindShader(*_compositorShader);
    renderer.setUniform(*_oneOverGammaUniform, 1.0f / (float)_gamma);
    renderer.setUniform(*_exposureUniform, (float)_exposure);
    renderer.bindTexture(_frameBuffer->targets()[0], 0);
    renderer.bindMesh(*_windowMesh);
    renderer.draw();

    renderer.endFrame();
}

double DeferredRenderingSystem::gamma() const
{
    return _gamma;
}

void DeferredRenderingSystem::setGamma(double gamma)
{
    _gamma = gamma;
    LOG_DEBUG(format("Gamma: %f", gamma));
}

double DeferredRenderingSystem::exposure() const
{
    return _exposure;
}

void DeferredRenderingSystem::setExposure(double exposure)
{
    _exposure = exposure;
    LOG_DEBUG(format("Exposure: %f", exposure));
}