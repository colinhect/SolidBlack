#pragma once

#include <Hect.h>
using namespace hect;

#include "States/SolidBlackState.h"
#include "Systems/FreeCameraControllerSystem.h"
#include "SolidBlackScene.h"

class ClientState :
    public SolidBlackState,
    public Uncopyable
{
public:
    ClientState(Engine& engine);
    ~ClientState();

    void begin();
    void end();

    void update(double timeStep);
    void render(double delta);

    void receiveKeyboardEvent(const KeyboardEvent& event);

private:
    void _receivePacketEvent(SocketEvent& event);

    void _sendAuthorization();

    Socket _socket;
    Peer _server;

    AssetCache _assetCache;

    FreeCameraControllerSystem _freeCameraControllerSystem;

    SolidBlackScene _scene;
};