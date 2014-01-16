#pragma once

#include <Hect.h>
using namespace hect;

#include "Components/PlayerCamera.h"
#include "Systems/PlayerCameraSystem.h"

class MainLogicLayer :
    public LogicLayer,
    public Listener<KeyboardEvent>,
    public Uncopyable
{
public:
    MainLogicLayer(AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer);
    ~MainLogicLayer();
    
    void fixedUpdate(double timeStep);
    void frameUpdate(double delta);

    void receiveEvent(const KeyboardEvent& event);

private:
    AssetCache* _assetCache;
    InputSystem* _input;
    Window* _window;

    CameraSystem _cameraSystem;
    BasicRenderSystem _renderSystem;
    PhysicsSystem _physicsSystem;

    PlayerCameraSystem _playerCameraSystem;

    Scene _scene;
};