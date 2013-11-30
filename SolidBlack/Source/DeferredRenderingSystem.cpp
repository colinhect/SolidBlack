#include "DeferredRenderingSystem.h"

DeferredRenderingSystem::DeferredRenderingSystem(Renderer& renderer, AssetCache& assetCache, const DataValue& settings) :
    RenderingSystem(renderer),
    _oneOverGammaUniform(nullptr),
    _exposureUniform(nullptr),
    _gamma(2.2),
    _exposure(0.025),
    _buffersInitialized(false)
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
}

void DeferredRenderingSystem::addMesh(Mesh& mesh, const Material& material, const Transform& transform)
{
    if (!material.techniques().empty())
    {
        const Technique& technique = material.techniques()[0];
        for (const Pass& pass : technique.passes())
        {
            MeshTask task;
            task.mesh = &mesh;
            task.pass = &pass;
            task.transform = &transform;
            _meshTasks.push_back(task);
        }
    }
}

void DeferredRenderingSystem::renderAll(Camera& camera, RenderTarget& target)
{
    if (!_buffersInitialized)
    {
        _buffersInitialized = true;


        unsigned width = target.width();
        unsigned height = target.height();

        PixelType pixelType = PixelType::Half;
        PixelFormat pixelFormat = PixelFormat::Rgba;
        TextureFilter filter = TextureFilter::Nearest;
        
        Texture::Array targets;
        targets.push_back(Texture(width, height, pixelType, pixelFormat, filter, filter, false, false)); // Color
        targets.push_back(Texture(width, height, pixelType, pixelFormat, filter, filter, false, false)); // Normal
        _geometryBuffer = FrameBuffer(targets);

        targets.clear();
        targets.push_back(Texture(width, height, pixelType, pixelFormat, filter, filter, false, false)); // Lighting
        _lightBuffer = FrameBuffer(targets);
    }

    renderer().beginFrame();
    renderer().bindTarget(_geometryBuffer);
    renderer().clear();

    //
    _meshTasks.clear();

    // Enqueue tasks from all visible renderables
    for (Entity& entity : entities())
    {
        Renderable& renderable = entity.component<Renderable>();
        renderable.render(camera, *this);
    }

    // Render mesh tasks
    for (const MeshTask& task : _meshTasks)
    {
        _renderMeshTask(task, camera, target);
    }

    renderer().endFrame();

    renderer().beginFrame();
    renderer().bindTarget(target);
    renderer().clear();

    renderer().bindShader(*_compositorShader);
    renderer().setUniform(*_oneOverGammaUniform, 1.0f / (float)_gamma);
    renderer().setUniform(*_exposureUniform, (float)_exposure);
    renderer().bindTexture(_geometryBuffer.targets()[0], 0);
    renderer().bindTexture(_geometryBuffer.targets()[1], 1);
    renderer().bindMesh(*_windowMesh);
    renderer().draw();

    renderer().endFrame();
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

void DeferredRenderingSystem::_renderMeshTask(const MeshTask& task, Camera& camera, const RenderTarget& target)
{
    Mesh& mesh = *task.mesh;
    const Pass& pass = *task.pass;
    const Transform& transform = *task.transform;

    renderMesh(mesh, pass, transform, camera, target);
}