#pragma once

class ProxySystem :
    public System,
    public Uncopyable
{
public:
    ProxySystem(AssetCache& assetCache, Socket& socket);

    bool includesEntity(const Entity& entity) const;

    void addEntity(Entity& entity);
    void removeEntity(Entity& entity);

    void createAll(Peer peer);

private:
    void _createCreationPacket(Entity& entity, Packet& packet);
    void _createDestructionPacket(Entity& entity, Packet& packet);

    AssetCache* _assetCache;
    Socket* _socket;
};