#include "MainLogicLayer.h"


MainLogicLayer::MainLogicLayer(AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer) :
    _assetCache(&assetCache),
    _input(&inputSystem),
    _window(&window),
    _renderSystem(renderer),
    _playerCameraSystem(inputSystem)
{
    EntitySerializer& entitySerializer = _scene.entitySerializer();
    entitySerializer.registerComponent<PlayerCamera, PlayerCameraSerializer>("PlayerCamera");

    _scene.addSystem(_cameraSystem);
    _scene.addSystem(_renderSystem);
    _scene.addSystem(_physicsSystem);
    _scene.addSystem(_playerCameraSystem);

    DataValue& sceneDataValue = assetCache.get<DataValue>("Scene.scene");
    _scene.load(sceneDataValue, assetCache);

    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.addListener(*this);

    _window->setCursorLocked(true);
}

MainLogicLayer::~MainLogicLayer()
{
    Dispatcher<KeyboardEvent>& keyboardDispatcher = _input->keyboard().dispatcher();
    keyboardDispatcher.removeListener(*this);
}

void MainLogicLayer::fixedUpdate(double timeStep)
{
    _cameraSystem.update();
    _physicsSystem.update(timeStep, 1);
    _playerCameraSystem.update(timeStep);
    _scene.refresh();

    _input->updateAxes(timeStep);
}

void MainLogicLayer::frameUpdate(double delta)
{
    delta;

    if (!_cameraSystem.hasCamera())
    {
        return;
    }

    Camera& camera = _cameraSystem.camera();
    camera.setAspectRatio(_window->aspectRatio());

    _renderSystem.renderAll(camera, *_window);

    _window->swapBuffers();
}

void MainLogicLayer::receiveEvent(const KeyboardEvent& event)
{
    if (event.type != KeyboardEventType::KeyDown)
    {
        return;
    }

    if (event.key == Key::Esc)
    {
        setActive(false);
    }
}