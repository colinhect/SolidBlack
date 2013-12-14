#pragma once

class ProxySystem :
    public System,
    public Uncopyable
{
public:
    ProxySystem(Scene& scene, AssetCache& assetCache, Socket& socket);

    bool includesEntity(const Entity& entity) const;

    void addEntity(Entity& entity);
    void removeEntity(Entity& entity);

    void broadcastAll(Peer peer);

private:
    void _createBroadcastPacket(Entity& entity, Packet& packet);

    Scene* _scene;
    AssetCache* _assetCache;
    Socket* _socket;
};