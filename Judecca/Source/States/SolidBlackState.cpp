#include "SolidBlackState.h"

#include "States/GalaxyViewerState.h"

SolidBlackState::SolidBlackState(Engine& engine) :
    State(engine, 1.0 / 60.0),
    _assetCache(engine.storage()),
    _galaxyScene(32),
    _hdrCompositorShader(_assetCache.get<Shader>("Shaders/HdrCompositor.shader")),
    _screenMesh(_assetCache.get<Mesh>("Meshes/Screen.mesh")),
    _oneOverGammaParameter(&_hdrCompositorShader->parameterWithName("oneOverGamma")),
    _exposureParameter(&_hdrCompositorShader->parameterWithName("exposure")),
    _gamma(2.2),
    _exposure(0.025),
    _debugLevel(0)
{
    // Create the input axes
    InputAxis viewX("ViewX", InputAxis::MouseMoveX);
    viewX.setAcceleration(0.0025);
    viewX.setGravity(10);

    InputAxis viewY("ViewY", InputAxis::MouseMoveY);
    viewY.setAcceleration(0.0025);
    viewY.setGravity(10);

    InputAxis moveX("MoveX", InputAxis::Key);
    moveX.setPositiveKey(Keyboard::D);
    moveX.setNegativeKey(Keyboard::A);
    moveX.setAcceleration(4);
    moveX.setGravity(10);

    InputAxis moveY("MoveY", InputAxis::Key);
    moveY.setPositiveKey(Keyboard::W);
    moveY.setNegativeKey(Keyboard::S);
    moveY.setAcceleration(4);
    moveY.setGravity(10);

    InputAxis roll("Roll", InputAxis::Key);
    roll.setPositiveKey(Keyboard::E);
    roll.setNegativeKey(Keyboard::Q);
    roll.setAcceleration(4);
    roll.setGravity(10);

    InputAxis adjustSpeed("AdjustSpeed", InputAxis::MouseScroll);
    adjustSpeed.setAcceleration(4);
    adjustSpeed.setGravity(1000);

    InputAxis::Array axes;
    axes.push_back(viewX);
    axes.push_back(viewY);
    axes.push_back(moveX);
    axes.push_back(moveY);
    axes.push_back(roll);
    axes.push_back(adjustSpeed);

    engine.input().setAxes(axes);
}

void SolidBlackState::begin()
{
    Screen& screen = engine().screen();

    Texture::Array targets;
    targets.push_back(Texture(screen.width(), screen.height(), Image::Float16, Image::Rgb, Texture::Nearest, Texture::Nearest, false, false));
    _frameBuffer.reset(new FrameBuffer(targets));

    _galaxyScene.addSystem(_cameraSystem);
    _galaxyScene.addSystem(_renderingSystem);
    _galaxyScene.addSystem(_debugRenderingSystem);

    Input& input = engine().input();
    input.keyboard().addListener(this);
    input.mouse().setCursorLocked(true);
}

void SolidBlackState::end()
{
    Input& input = engine().input();
    input.keyboard().removeListener(this);
}

void SolidBlackState::update(double timeStep)
{
    _cameraSystem.update();
}

void SolidBlackState::render(double delta)
{
    if (!_cameraSystem.hasCamera())
    {
        return;
    }

    Gpu& gpu = engine().gpu();
    FrameBuffer& renderTarget = *_frameBuffer;
    Screen& screen = engine().screen();

    Camera& camera = _cameraSystem.camera();

    // Render scene to floating point frame buffer
    gpu.beginFrame();
    gpu.bindTarget(renderTarget);
    gpu.clear();
    _renderingSystem.renderAll(camera, gpu, renderTarget);
    gpu.endFrame();

    // Render the tonemapped frame buffer
    gpu.beginFrame();
    gpu.bindTarget(screen);
    gpu.clear();

    gpu.bindShader(*_hdrCompositorShader);
    gpu.setShaderParameter(*_oneOverGammaParameter, 1.0f / (float)_gamma);
    gpu.setShaderParameter(*_exposureParameter, (float)_exposure);
    gpu.bindTexture(_frameBuffer->targets()[0], 0);
    gpu.bindMesh(*_screenMesh);
    gpu.draw();

    // Draw debug info
    if (debugLevel() == 1)
    {
        _debugRenderingSystem.renderAll(camera, gpu, screen);
    }
    gpu.endFrame();

    engine().swapBuffers();
}

void SolidBlackState::notifyKeyboardEvent(const Keyboard::Event& event)
{
    if (event.type != Keyboard::Event::KeyDown)
    {
        return;
    }

    if (event.key == Keyboard::Esc)
    {
        setActive(false);
    }
    else if (event.key == Keyboard::Tab)
    {
        Mouse& mouse = engine().input().mouse();
        mouse.setCursorLocked(!mouse.isCursorLocked());
    }
    else if (event.key == Keyboard::F1)
    {
        if (_debugLevel == 1)
        {
            _debugLevel = 0;
        }
        else
        {
            _debugLevel = 1;
        }
    }
    else if (event.key == Keyboard::F5)
    {
        engine().pushState<GalaxyViewerState>(engine());
        setActive(false);
    }
    else if (event.key == Keyboard::X)
    {
        _exposure *= 2.0;
        LOG_DEBUG(format("Exposure: %f", _exposure));
    }
    else if (event.key == Keyboard::Z)
    {
        _exposure /= 2.0;
        LOG_DEBUG(format("Exposure: %f", _exposure));
    }
    else if (event.key == Keyboard::V)
    {
        _gamma += 0.1;
        LOG_DEBUG(format("Gamma: %f", _gamma));
    }
    else if (event.key == Keyboard::C)
    {
        _gamma -= 0.1;
        LOG_DEBUG(format("Gamma: %f", _gamma));
    }
}

AssetCache& SolidBlackState::assetCache()
{
    return _assetCache;
}

Scene& SolidBlackState::galaxyScene()
{
    return _galaxyScene;
}

unsigned SolidBlackState::debugLevel() const
{
    return _debugLevel;
}