#pragma once

#include "Common/States/SolidBlackState.h"
#include "Common/Systems/FreeCameraControllerSystem.h"

#include "Player.h"
#include "Bubble.h"

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
    void _connectionEvent(Socket::Event& event);
    void _disconnectionEvent(Socket::Event& event);
    void _receivePacketEvent(Socket::Event& event);

    void _sendAuthorizationRequest(Peer peer);

    enum
    {
        MaxPlayerCount = 128,
        Port = 6006,
        ChannelCount = 2
    };

    AssetCache _assetCache;
    Socket _socket;
    Player _players[MaxPlayerCount];

    Bubble::RefArray _bubbles;
};

/*
#pragma once

#include "Common/States/SolidBlackState.h"
#include "Common/Systems/FreeCameraControllerSystem.h"

#include "Player.h"

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
    enum {
        MaxPlayerCount = 128,
        Port = 6006,
        ChannelCount = 2
    };

    AssetCache _assetCache;
    Socket _socket;
    Player players[MaxPlayerCount];

    CameraSystem _cameraSystem;
    RenderingSystem _renderingSystem;
    DebugRenderingSystem _debugRenderingSystem;

    FreeCameraControllerSystem _freeCameraControllerSystem;

    Scene _scene;
};
*/