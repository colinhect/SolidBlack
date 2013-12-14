#pragma once

class ServerLogicLayer :
    public LogicLayer,
    public ServerListener,
    public Uncopyable
{
public:
    ServerLogicLayer(AssetCache& assetCache);

    void fixedUpdate(double timeStep);

    void receivePacket(const Player& player, PacketType type, PacketReadStream& stream);

private:
    Server _server;

    PhysicsSystem _physicsSystem;
    Scene _scene;
    ProxySystem _proxySystem;
};