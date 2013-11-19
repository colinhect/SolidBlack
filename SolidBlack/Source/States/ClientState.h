#pragma once

#include <Hect.h>
using namespace hect;

#include "States/SolidBlackState.h"
#include "Systems/FreeCameraControllerSystem.h"

class ClientState :
    public SolidBlackState
{
public:
    ClientState(Engine& engine);
    ~ClientState();

    void begin();
    void end();

    void update(double timeStep);
    void render(double delta);

private:
    void _receivePacketEvent(Socket::Event& event);

    void _sendAuthorization();

    Socket _socket;
    Peer _server;

    AssetCache _assetCache;

    CameraSystem _cameraSystem;
    RenderingSystem _renderingSystem;
    DebugRenderingSystem _debugRenderingSystem;

    FreeCameraControllerSystem _freeCameraControllerSystem;

    Scene _scene;
};