#include "TestState.h"

#include "PacketType.h"
#include "FreeCameraController.h"

TestState::TestState(Engine& engine) :
    State(engine, 1.0 / 60.0),
    _assetCache(engine.storage()),
    _renderingSystem(_assetCache, engine.settings()),
    _freeCameraControllerSystem(engine.input()),
    _scene(_assetCache)
{
    _scene.registerSerializer<FreeCameraController, ComponentSerializer<FreeCameraController>>("FreeCameraController");
}

void TestState::begin()
{
    _scene.addSystem(_cameraSystem);
    _scene.addSystem(_renderingSystem);
    _scene.addSystem(_freeCameraControllerSystem);

    Keyboard& keyboard = engine().input().keyboard();
    keyboard.addListener(*this);

    Mouse& mouse = engine().input().mouse();
    mouse.setCursorLocked(true);

    _scene.createEntity("Entities/FreeCamera.entity");
    _scene.createEntity("Entities/TestCube.entity");

    _scene.refresh();
}

void TestState::end()
{
    Keyboard& keyboard = engine().input().keyboard();
    keyboard.removeListener(*this);

    _scene.addSystem(_freeCameraControllerSystem);
    _scene.addSystem(_renderingSystem);
    _scene.addSystem(_cameraSystem);
}

void TestState::update(double timeStep)
{
    _cameraSystem.update();
    _freeCameraControllerSystem.update(timeStep);
    _scene.refresh();
}

void TestState::render(double delta)
{
    if (!_cameraSystem.hasCamera())
    {
        return;
    }

    Camera& camera = _cameraSystem.camera();
    camera.setAspectRatio(engine().screen().aspectRatio());
    _renderingSystem.renderAll(camera, engine().gpu(), engine().screen());

    engine().swapBuffers();
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
        Mouse& mouse = engine().input().mouse();
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