#include "SolidBlack.h"

TestState::TestState(AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer, const DataValue& settings) :
    _assetCache(&assetCache),
    _input(&inputSystem),
    _window(&window),
    _renderingSystem(renderer, assetCache, settings),
    _debugCameraSystem(inputSystem)
{
    _entitySerializer.registerComponent<DebugCamera, DebugCameraSerializer>("DebugCamera");

    _scene.addSystem(_cameraSystem);
    _scene.addSystem(_renderingSystem);
    _scene.addSystem(_debugCameraSystem);

    _input->keyboard().addListener(*this);
    _window->setCursorLocked(true);
    
    // Create debug camera
    _debugCamera = _scene.createEntity();
    _entitySerializer.deserialize(_debugCamera, assetCache, "Entities/FreeCamera.entity");
    _debugCamera.activate();

    // Create a test cube prefab
    _testCube = _scene.createEntity();
    _entitySerializer.deserialize(_testCube, assetCache, "Entities/TestCube.entity");

    // Activate one at the origin
    _testCube.clone().activate();

    // Create the sun
    Entity sun = _scene.createEntity();
    _entitySerializer.deserialize(sun, assetCache, "Entities/Sun.entity");
    sun.activate();

    _scene.refresh();
}

TestState::~TestState()
{
    _input->keyboard().removeListener(*this);
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
        Entity testCube = _testCube.clone();
        if (_debugCamera && _debugCamera.hasComponent<Transform>())
        {
            testCube.component<Transform>() = _debugCamera.component<Transform>();
        }
        testCube.activate();
    }
    else if (event.key == Key::Tab)
    {
        bool cursorLocked = _window->isCursorLocked();
        _window->setCursorLocked(!cursorLocked);
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