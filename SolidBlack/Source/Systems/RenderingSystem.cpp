#include "SolidBlack.h"

RenderingSystem::RenderingSystem(Renderer& renderer, AssetCache& assetCache) :
    _renderer(&renderer),
    _ambientLightColorUniform(nullptr),
    _directionalLightColorUniform(nullptr),
    _directionalLightDirectionUniform(nullptr),
    _directionalLightViewUniform(nullptr),
    _oneOverGammaUniform(nullptr),
    _exposureUniform(nullptr),
    _gamma(2.2),
    _exposure(0.025),
    _buffersInitialized(false)
{
    // Set up additive blending
    _additiveLightMode.enableState(RenderState::Blend);
    _additiveLightMode.disableState(RenderState::DepthTest);

    // Load ambient light shader
    _ambientLightShader = assetCache.get<Shader>("DeferredShading/AmbientLight.shader");
    _ambientLightColorUniform = &_ambientLightShader->uniformWithName("color");

    // Load directional light shader
    _directionalLightShader = assetCache.get<Shader>("DeferredShading/DirectionalLight.shader");
    _directionalLightColorUniform = &_directionalLightShader->uniformWithName("color");
    _directionalLightDirectionUniform = &_directionalLightShader->uniformWithName("direction");
    _directionalLightViewUniform = &_directionalLightShader->uniformWithName("view");

    // Load compositor shader
    _compositorShader = assetCache.get<Shader>("DeferredShading/Compositor.shader");
    _oneOverGammaUniform = &_compositorShader->uniformWithName("oneOverGamma");
    _exposureUniform = &_compositorShader->uniformWithName("exposure");

    // Load screen mesh
    _screenMesh = assetCache.get<Mesh>("DeferredShading/Screen.mesh");
}

void RenderingSystem::addEntity(Entity& entity)
{
    if (entity.hasComponent<Geometry>() && entity.hasComponent<Transform>())
    {
        System::addEntity(entity);
        _geometryComponents.push_back(&entity.component<Geometry>());
        _transformComponents.push_back(&entity.component<Transform>());
    }
    else if (entity.hasComponent<AmbientLight>())
    {
        System::addEntity(entity);
        _ambientLightComponents.push_back(&entity.component<AmbientLight>());
    }
    else if (entity.hasComponent<DirectionalLight>())
    {
        System::addEntity(entity);
        _directionalLightComponents.push_back(&entity.component<DirectionalLight>());
    }
}

void RenderingSystem::removeEntity(Entity& entity)
{
    if (entity.hasComponent<Geometry>() && entity.hasComponent<Transform>())
    {
        System::removeEntity(entity);
        _geometryComponents.erase(std::remove(_geometryComponents.begin(), _geometryComponents.end(), &entity.component<Geometry>()), _geometryComponents.end());
        _transformComponents.erase(std::remove(_transformComponents.begin(), _transformComponents.end(), &entity.component<Transform>()), _transformComponents.end());
    }
    else if (entity.hasComponent<AmbientLight>())
    {
        System::removeEntity(entity);
        _ambientLightComponents.erase(std::remove(_ambientLightComponents.begin(), _ambientLightComponents.end(), &entity.component<AmbientLight>()), _ambientLightComponents.end());
    }
    else if (entity.hasComponent<DirectionalLight>())
    {
        System::removeEntity(entity);
        _directionalLightComponents.erase(std::remove(_directionalLightComponents.begin(), _directionalLightComponents.end(), &entity.component<DirectionalLight>()), _directionalLightComponents.end());
    }
}

void RenderingSystem::renderAll(Camera& camera, RenderTarget& target)
{
    // Initialize buffers if needed
    if (!_buffersInitialized)
    {
        _initializeBuffers(target.width(), target.height());
    }

    // Begin geometry buffer rendering
    _renderer->beginFrame();
    _renderer->bindTarget(_geometryBuffer);
    _renderer->clear();

    // Render geometery
    size_t geometryCount = _geometryComponents.size();
    for (size_t i = 0; i < geometryCount; ++i)
    {
        Geometry& geometry = *_geometryComponents[i];
        Transform& transform = *_transformComponents[i];

        Mesh& mesh = *geometry.mesh().get();
        Material& material = *geometry.material().get();

        // Render the mesh for each pass
        for (const Pass& pass : material.techniques()[0].passes())
        {
            _renderMeshPass(camera, target, pass, mesh, transform);
        }
    }

    // End geometry buffer rendering
    _renderer->endFrame();

    // Begin light buffer rendering
    _renderer->beginFrame();
    _renderer->bindTarget(_lightingBuffer);
    _renderer->clear();

    // Bind the normal texture from the geometry buffer
    _renderer->bindTexture(_geometryBuffer.targets()[1], 0);

    // Bind the screen mesh and light rendering mode
    _renderer->bindMesh(*_screenMesh);
    _renderer->bindMode(_additiveLightMode);

    // Render ambient lights
    _renderer->bindShader(*_ambientLightShader);
    for (AmbientLight* light : _ambientLightComponents)
    {
        Vector3<float> color = light->color();
        _renderer->setUniform(*_ambientLightColorUniform, color);
        _renderer->draw();
    }

    // Render directional lights
    _renderer->bindShader(*_directionalLightShader);
    _renderer->setUniform(*_directionalLightViewUniform, (Matrix4<float>)camera.viewMatrix());
    for (DirectionalLight* light : _directionalLightComponents)
    {
        Vector3<float> color = light->color();
        Vector3<float> direction = light->direction();
        _renderer->setUniform(*_directionalLightColorUniform, color);
        _renderer->setUniform(*_directionalLightDirectionUniform, direction);
        _renderer->draw();
    }

    // End light buffer rendering
    _renderer->endFrame();

    // Begin compositor rendering
    _renderer->beginFrame();
    _renderer->bindTarget(target);
    _renderer->clear();

    // Being the compositor and set the uniform values
    _renderer->bindShader(*_compositorShader);
    _renderer->setUniform(*_oneOverGammaUniform, 1.0f / (float)_gamma);
    _renderer->setUniform(*_exposureUniform, (float)_exposure);

    // Bind the color and lighting buffers.
    _renderer->bindTexture(_geometryBuffer.targets()[0], 0);
    _renderer->bindTexture(_lightingBuffer.targets()[0], 1);

    // Bind and draw the final image
    _renderer->bindMesh(*_screenMesh);
    _renderer->draw();

    // End compositor rendering
    _renderer->endFrame();
}

double RenderingSystem::gamma() const
{
    return _gamma;
}

void RenderingSystem::setGamma(double gamma)
{
    _gamma = gamma;
    LOG_DEBUG(format("Gamma: %f", gamma));
}

double RenderingSystem::exposure() const
{
    return _exposure;
}

void RenderingSystem::setExposure(double exposure)
{
    _exposure = exposure;
    LOG_DEBUG(format("Exposure: %f", exposure));
}

void RenderingSystem::_renderMeshPass(const Camera& camera, const RenderTarget& target, const Pass& pass, Mesh& mesh, const Transform& transform)
{
    // Prepare the pass
    pass.prepare(*_renderer);

    // Buid the model matrix
    Matrix4<> model;
    transform.buildMatrix(model);

    // Set uniforms with bindings
    Shader& shader = *pass.shader();
    for (const Uniform& uniform : shader.uniforms())
    {
        if (uniform.hasBinding())
        {
            UniformBinding binding = uniform.binding();

            switch (binding)
            {
            case UniformBinding::RenderTargetSize:
                _renderer->setUniform(uniform, Vector2<float>((float)target.width(), (float)target.height()));
                break;
            case UniformBinding::CameraPosition:
                _renderer->setUniform(uniform, (Vector3<float>)camera.position());
                break;
            case UniformBinding::CameraUp:
                _renderer->setUniform(uniform, (Vector3<float>)camera.up());
                break;
            case UniformBinding::ViewMatrix:
                _renderer->setUniform(uniform, (Matrix4<float>)camera.viewMatrix());
                break;
            case UniformBinding::ProjectionMatrix:
                _renderer->setUniform(uniform, (Matrix4<float>)camera.projectionMatrix());
                break;
            case UniformBinding::ViewProjectionMatrix:
                _renderer->setUniform(uniform, (Matrix4<float>)(camera.projectionMatrix() * camera.viewMatrix()));
                break;
            case UniformBinding::ModelMatrix:
                _renderer->setUniform(uniform, (Matrix4<float>)model);
                break;
            case UniformBinding::ModelViewMatrix:
                _renderer->setUniform(uniform, (Matrix4<float>)(camera.viewMatrix() * model));
                break;
            case UniformBinding::ModelViewProjectionMatrix:
                _renderer->setUniform(uniform, (Matrix4<float>)(camera.projectionMatrix() * (camera.viewMatrix() * model)));
                break;
            }
        }
    }

    // Bind and draw the mesh
    _renderer->bindMesh(mesh);
    _renderer->draw();

}

void RenderingSystem::_initializeBuffers(unsigned width, unsigned height)
{
    _buffersInitialized = true;

    PixelType pixelType = PixelType::Half;
    PixelFormat pixelFormat = PixelFormat::Rgba;
    TextureFilter filter = TextureFilter::Nearest;

    Texture::Array targets;

    // Color: R G B ?
    targets.push_back(Texture("Color", width, height, pixelType, pixelFormat, filter, filter, false, false));

    // Normal: X Y Z Depth
    targets.push_back(Texture("Normal", width, height, pixelType, pixelFormat, filter, filter, false, false));
    _geometryBuffer = FrameBuffer(targets);

    targets.clear();
    targets.push_back(Texture("Lighting", width, height, pixelType, PixelFormat::Rgb, filter, filter, false, false));
    _lightingBuffer = FrameBuffer(targets);
}