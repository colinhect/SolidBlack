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
    
    // Load screen mesh
    std::string screenMeshPath = settings["graphics"]["screenMesh"].asString();
    LOG_INFO(format("Using screen mesh: '%s'", screenMeshPath.c_str()));
    _screenMesh = assetCache.get<Mesh>(screenMeshPath);

    LOG_INFO("Done");
}

void DeferredRenderingSystem::renderAll(Camera& camera, Gpu& gpu, RenderTarget& target)
{
    if (!_frameBuffer || _frameBuffer->width() != target.width() || _frameBuffer->height() != target.height())
    {
        Texture::Array targets;
        targets.push_back(Texture(target.width(), target.height(), PixelType::Half, PixelFormat::Rgb, TextureFilter::Nearest, TextureFilter::Nearest, false, false));
        _frameBuffer.reset(new FrameBuffer(targets));
    }

    // Render scene to floating point frame buffer
    gpu.beginFrame();
    gpu.bindTarget(*_frameBuffer);
    gpu.clear();
    RenderingSystem::renderAll(camera, gpu, *_frameBuffer);
    gpu.endFrame();

    // Render the tonemapped frame buffer
    gpu.beginFrame();
    gpu.bindTarget(target);
    gpu.clear();

    gpu.bindShader(*_compositorShader);
    gpu.setUniform(*_oneOverGammaUniform, 1.0f / (float)_gamma);
    gpu.setUniform(*_exposureUniform, (float)_exposure);
    gpu.bindTexture(_frameBuffer->targets()[0], 0);
    gpu.bindMesh(*_screenMesh);
    gpu.draw();

    gpu.endFrame();
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