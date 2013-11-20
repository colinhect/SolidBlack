#pragma once

#include "States/SolidBlackState.h"
#include "Systems/FreeCameraControllerSystem.h"

#include "Server/Player.h"
#include "Server/Bubble.h"

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
    void _connectionEvent(SocketEvent& event);
    void _disconnectionEvent(SocketEvent& event);
    void _receivePacketEvent(SocketEvent& event);

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