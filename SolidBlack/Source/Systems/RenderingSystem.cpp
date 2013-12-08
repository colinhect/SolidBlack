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
    _additiveLightMode.setBlendFactors(BlendFactor::One, BlendFactor::One);
    
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

bool RenderingSystem::includesEntity(const Entity& entity) const
{
    return entity.hasComponent<Geometry>() || entity.hasComponent<AmbientLight>() || entity.hasComponent<DirectionalLight>();
}

void RenderingSystem::renderAll(Camera& camera, RenderTarget& target)
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
        targets.push_back(Texture("Color", width, height, pixelType, pixelFormat, filter, filter, false, false));
        targets.push_back(Texture("Normal", width, height, pixelType, pixelFormat, filter, filter, false, false));
        _geometryBuffer = FrameBuffer(targets);

        targets.clear();
        targets.push_back(Texture("Lighting", width, height, pixelType, pixelFormat, filter, filter, false, false));
        _lightBuffer = FrameBuffer(targets);
    }

    _renderer->beginFrame();
    _renderer->bindTarget(_geometryBuffer);
    _renderer->clear();

    // Render geometer
    for (Entity& entity : entities())
    {
        if (entity.hasComponent<Geometry>() && entity.hasComponent<Transform>())
        {
            Geometry& geometry = entity.component<Geometry>();
            Transform& transform = entity.component<Transform>();

            Mesh& mesh = *geometry.mesh().get();
            Material& material = *geometry.material().get();

            for (const Pass& pass : material.techniques()[0].passes())
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
        }
    }

    _renderer->endFrame();

    _renderer->beginFrame();
    _renderer->bindTarget(_lightBuffer);
    _renderer->clear();

    _renderer->bindTexture(_geometryBuffer.targets()[0], 0);
    _renderer->bindTexture(_geometryBuffer.targets()[1], 1);

    _renderer->bindMesh(*_screenMesh);
    _renderer->bindMode(_additiveLightMode);

    _renderer->bindShader(*_ambientLightShader);
    for (Entity& entity : entities())
    {
        if (entity.hasComponent<AmbientLight>())
        {
            AmbientLight& light = entity.component<AmbientLight>();
            _renderer->setUniform(*_ambientLightColorUniform, (Vector3<float>)light.color());

            _renderer->draw();
        }
    }

    _renderer->bindShader(*_directionalLightShader);
    _renderer->setUniform(*_directionalLightViewUniform, (Matrix4<float>)camera.viewMatrix());
    for (Entity& entity : entities())
    {
        if (entity.hasComponent<DirectionalLight>())
        {
            DirectionalLight& light = entity.component<DirectionalLight>();
            _renderer->setUniform(*_directionalLightColorUniform, (Vector3<float>)light.color());
            _renderer->setUniform(*_directionalLightDirectionUniform, (Vector3<float>)light.direction());

            _renderer->draw();
        }
    }

    _renderer->endFrame();

    _renderer->beginFrame();
    _renderer->bindTarget(target);
    _renderer->clear();

    _renderer->bindShader(*_compositorShader);
    _renderer->setUniform(*_oneOverGammaUniform, 1.0f / (float)_gamma);
    _renderer->setUniform(*_exposureUniform, (float)_exposure);
    _renderer->bindTexture(_geometryBuffer.targets()[0], 0);
    _renderer->bindTexture(_lightBuffer.targets()[0], 1);
    _renderer->bindMesh(*_screenMesh);
    _renderer->draw();

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