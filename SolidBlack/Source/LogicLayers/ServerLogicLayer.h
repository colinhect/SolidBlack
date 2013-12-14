#pragma once

class ServerLogicLayer :
    public LogicLayer,
    public Uncopyable
{
public:
    ServerLogicLayer(AssetCache& assetCache);

    void fixedUpdate(double timeStep);

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

    Socket _socket;
    Player _players[MaxPlayerCount];

    PhysicsSystem _physicsSystem;

    Scene _scene;

    ProxySystem _proxySystem;
};