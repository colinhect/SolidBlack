#include "TestState.h"

#include "PacketType.h"
#include "FreeCameraController.h"

TestState::TestState(FileSystem& fileSystem, InputSystem& inputSystem, Window& window, Renderer& renderer, const DataValue& settings) :
    State(1.0 / 60.0),
    _fileSystem(&fileSystem),
    _input(&inputSystem),
    _window(&window),
    _renderer(&renderer),
    _assetCache(fileSystem),
    _renderingSystem(_assetCache, settings),
    _scene(inputSystem, _assetCache)
{
    _scene.registerComponent<FreeCameraController, FreeCameraControllerSerializer>("FreeCameraController");
}

void TestState::begin(Flow& flow)
{
    _scene.addSystem(_cameraSystem);
    _scene.addSystem(_renderingSystem);
    _scene.addSystem(_behaviorSystem);

    Keyboard& keyboard = _input->keyboard();
    keyboard.addListener(*this);

    Mouse& mouse = _input->mouse();
    mouse.setCursorLocked(true);

    _scene.createEntity("Entities/FreeCamera.entity");
    _scene.createEntity("Entities/TestCube.entity");

    _scene.refresh();
}

void TestState::end(Flow& flow)
{
    Keyboard& keyboard = _input->keyboard();
    keyboard.removeListener(*this);

    _scene.addSystem(_behaviorSystem);
    _scene.addSystem(_renderingSystem);
    _scene.addSystem(_cameraSystem);
}

void TestState::update(double timeStep)
{
    _cameraSystem.update();
    _behaviorSystem.update(timeStep);
    _scene.refresh();

    _input->updateAxes(timeStep);
}

void TestState::render(double delta)
{
    if (!_cameraSystem.hasCamera())
    {
        return;
    }

    Camera& camera = _cameraSystem.camera();
    camera.setAspectRatio(_window->aspectRatio());
    _renderingSystem.renderAll(camera, *_renderer, *_window);

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
        setActive(false);
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