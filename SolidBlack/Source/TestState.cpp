#include "TestState.h"

#include "PacketType.h"
#include "DebugCamera.h"

TestState::TestState(AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer, const DataValue& settings) :
    _assetCache(&assetCache),
    _input(&inputSystem),
    _window(&window),
    _renderingSystem(renderer, assetCache, settings),
    _debugCameraSystem(inputSystem)
{
    _entitySerializer.registerComponent<Camera, CameraSerializer>("Camera");
    _entitySerializer.registerComponent<AmbientLight, AmbientLightSerializer>("AmbientLight");
    _entitySerializer.registerComponent<DirectionalLight, DirectionalLightSerializer>("DirectionalLight");
    _entitySerializer.registerComponent<Geometry, GeometrySerializer>("Geometry");
    _entitySerializer.registerComponent<Transform, TransformSerializer>("Transform");
    _entitySerializer.registerComponent<DebugCamera, DebugCameraSerializer>("DebugCamera");

    _scene.addSystem(_cameraSystem);
    _scene.addSystem(_renderingSystem);
    _scene.addSystem(_debugCameraSystem);

    Keyboard& keyboard = _input->keyboard();
    keyboard.addListener(*this);

    Mouse& mouse = _input->mouse();
    mouse.setCursorLocked(true);
    
    Entity freeCamera = _scene.createEntity();
    _entitySerializer.deserialize(freeCamera, assetCache, "Entities/FreeCamera.entity");
    freeCamera.activate();

    Entity testCube = _scene.createEntity();
    _entitySerializer.deserialize(testCube, assetCache, "Entities/TestCube.entity");
    testCube.activate();

    Entity sun = _scene.createEntity();
    _entitySerializer.deserialize(sun, assetCache, "Entities/Sun.entity");
    sun.activate();

    _scene.refresh();
}

TestState::~TestState()
{
    Keyboard& keyboard = _input->keyboard();
    keyboard.removeListener(*this);
}

void TestState::update(double timeStep)
{
    if (!isActivated())
    {
        return;
    }

    _cameraSystem.update();
    _debugCameraSystem.update(timeStep);
    _scene.refresh();

    _input->updateAxes(timeStep);
}

void TestState::render(double delta)
{
    if (!isActivated() || !_cameraSystem.hasCamera())
    {
        return;
    }

    Camera& camera = _cameraSystem.camera();
    camera.setAspectRatio(_window->aspectRatio());

    _renderingSystem.renderAll(camera, *_window);

    _window->swapBuffers();
}

void TestState::receiveKeyboardEvent(const KeyboardEvent& event)
{
    if (event.type != KeyboardEventType::KeyDown)
    {
        return;
    }

    if (event.key == Key::Esc)
    {
        setDone(true);
    }
    else if (event.key == Key::T)
    {
        Entity testCube = _scene.createEntity();
        _entitySerializer.deserialize(testCube, *_assetCache, "Entities/TestCube.entity");
        testCube.activate();

        Entity debugCamera = _scene.entityWithComponent<DebugCamera>();
        if (debugCamera && debugCamera.hasComponent<Transform>())
        {
            testCube.component<Transform>() = debugCamera.component<Transform>();
        }
    }
    else if (event.key == Key::Tab)
    {
        Mouse& mouse = _input->mouse();
        mouse.setCursorLocked(!mouse.isCursorLocked());
    }
    else if (event.key == Key::X)
    {
        _renderingSystem.setExposure(_renderingSystem.exposure() * 2.0);
    }
    else if (event.key == Key::Z)
    {
        _renderingSystem.setExposure(_renderingSystem.exposure() / 2.0);
    }
    else if (event.key == Key::V)
    {
        _renderingSystem.setGamma(_renderingSystem.gamma() + 0.1);
    }
    else if (event.key == Key::C)
    {
        _renderingSystem.setGamma(_renderingSystem.gamma() - 0.1);
    }
}