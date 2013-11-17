#pragma once

#include "Common/States/SolidBlackState.h"
#include "Common/Systems/FreeCameraControllerSystem.h"

class ServerState :
    public SolidBlackState
{
public:
    ServerState(Engine& engine);

    void begin();
    void end();

    void update(double timeStep);
    void render(double delta);

    void notifyKeyboardEvent(const Keyboard::Event& event);

private:
    AssetCache _assetCache;
    Socket _socket;

    CameraSystem _cameraSystem;
    RenderingSystem _renderingSystem;
    DebugRenderingSystem _debugRenderingSystem;

    FreeCameraControllerSystem _freeCameraControllerSystem;

    Scene _scene;
};