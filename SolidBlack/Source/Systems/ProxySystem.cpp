#include "SolidBlack.h"

ProxySystem::ProxySystem(Scene& scene, AssetCache& assetCache, Socket& socket) :
    _scene(&scene),
    _assetCache(&assetCache),
    _socket(&socket)
{
}

bool ProxySystem::includesEntity(const Entity& entity) const
{
    return entity.hasComponent<Proxy>();
}

void ProxySystem::addEntity(Entity& entity)
{
    System::addEntity(entity);

    LOG_INFO(format("Server: Proxying entity with ID '%d' to all", entity.id()));

    Packet packet(PacketFlag::Reliable);
    _createBroadcastPacket(entity, packet);
    _socket->broadcastPacket(0, packet);
    _socket->flush();
}

void ProxySystem::removeEntity(Entity& entity)
{
    Packet packet(PacketFlag::Reliable);
    PacketWriteStream stream = packet.writeStream();
    stream.writeByte((uint8_t)PacketType::DestroyEntity);
    stream.writeUnsignedInt((uint32_t)entity.id());
    _socket->broadcastPacket(0, packet);
    _socket->flush();

    System::removeEntity(entity);
}

void ProxySystem::broadcastAll(Peer peer)
{
    for (Entity& entity : entities())
    {
        LOG_INFO(format("Server: Proxying entity with ID '%d' to peer '%d'", entity.id(), peer.id()));

        Packet packet(PacketFlag::Reliable);
        _createBroadcastPacket(entity, packet);
        _socket->sendPacket(peer, 0, packet);
        _socket->flush();
    }
}

void ProxySystem::_createBroadcastPacket(Entity& entity, Packet& packet)
{
    Proxy& proxy = entity.component<Proxy>();

    PacketWriteStream stream = packet.writeStream();
    stream.writeByte((uint8_t)PacketType::CreateEntity);
    stream.writeUnsignedInt((uint32_t)entity.id());
    stream.writeString(proxy.entity());
}