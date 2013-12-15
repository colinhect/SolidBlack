#pragma once

class Server;

class ServerBubble :
    public ServerListener,
    public Uncopyable
{
public:
    typedef std::shared_ptr<ServerBubble> Ref;
    typedef std::vector<ServerBubble::Ref> RefArray;

    ServerBubble(Server& server, AssetCache& assetCache);
    ~ServerBubble();

    void fixedUpdate(double timeStep);

    void receivePacket(const Player& player, PacketType type, PacketReadStream& stream);

private:
    Server* _server;
    AssetCache* _assetCache;
    
    ProxySystem _proxySystem;
    PhysicsSystem _physicsSystem;

    Scene _scene;
};