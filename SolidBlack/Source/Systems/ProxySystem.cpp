#include "SolidBlack.h"

ProxySystem::ProxySystem(AssetCache& assetCache, Socket& socket) :
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

    LOG_TRACE(format("Server: Sending proxy entity creation for id '%d' to all", entity.id()));

    Packet packet(PacketFlag::Reliable);
    _createCreationPacket(entity, packet);
    _socket->broadcastPacket(1, packet);
}

void ProxySystem::removeEntity(Entity& entity)
{
    LOG_TRACE(format("Server: Sending proxy entity destruction for id '%d' to all", entity.id()));

    Packet packet(PacketFlag::Reliable);
    _createDestructionPacket(entity, packet);
    _socket->broadcastPacket(1, packet);

    System::removeEntity(entity);
}

void ProxySystem::createAll(Peer peer)
{
    for (Entity& entity : entities())
    {
        LOG_TRACE(format("Server: Sending proxy entity creation for id '%d' to peer '%d'", entity.id(), peer.id()));

        Packet packet(PacketFlag::Reliable);
        _createCreationPacket(entity, packet);
        _socket->sendPacket(peer, 1, packet);
    }
}

void ProxySystem::_createCreationPacket(Entity& entity, Packet& packet)
{
    Proxy& proxy = entity.component<Proxy>();

    PacketWriteStream stream = packet.writeStream();
    stream.writeByte((uint8_t)PacketType::CreateEntity);
    stream.writeUnsignedInt((uint32_t)entity.id());
    stream.writeString(proxy.entity());
}

void ProxySystem::_createDestructionPacket(Entity& entity, Packet& packet)
{
    PacketWriteStream stream = packet.writeStream();
    stream.writeByte((uint8_t)PacketType::DestroyEntity);
    stream.writeUnsignedInt((uint32_t)entity.id());
}