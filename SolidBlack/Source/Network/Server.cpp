#include "SolidBlack.h"

Server::Server() :
    _socket(Port, MaxPlayerCount, ChannelCount)
{
}

void Server::addListener(ServerListener& listener)
{
    if (std::find(_listeners.begin(), _listeners.end(), &listener) != _listeners.end())
    {
        return;  // This listener was already added
    }

    _listeners.push_back(&listener);
}

void Server::removeListener(ServerListener& listener)
{
    _listeners.erase(std::remove(_listeners.begin(), _listeners.end(), &listener), _listeners.end());
}

void Server::refresh()
{
    SocketEvent event;
    while (_socket.pollEvent(event))
    {
        switch (event.type)
        {
        case SocketEventType::Connect:
            _connectionEvent(event);
            break;
        case SocketEventType::Disconnect:
            _disconnectionEvent(event);
            break;
        case SocketEventType::Receive:
            _receivePacketEvent(event);
            break;
        }
    }
}

Socket& Server::socket()
{
    return _socket;
}

void Server::_connectionEvent(SocketEvent& event)
{
    Peer::Id peerId = event.peer.id();
    LOG_TRACE(format("Server: Peer '%d' connected", peerId));

    Player& player = _players[peerId];
    player.peer = event.peer;

    if (player.authorized)
    {
        LOG_TRACE(format("Server: Peer '%d' is already authorized as '%s'", peerId, player.name.c_str()));
    }
    else
    {
        _sendAuthorizationRequest(event.peer);
    }
}

void Server::_disconnectionEvent(SocketEvent& event)
{
    Peer::Id peerId = event.peer.id();
    Player& player = _players[peerId];
    if (player.authorized)
    {
        LOG_TRACE(format("Server: Peer '%d' (authorized as '%s') disconnected", peerId, player.name.c_str()));

        player.authorized = false;
        player.name = "";
    }
    else
    {
        LOG_TRACE(format("Server: Peer '%d' (unauthorized) disconnected", peerId));
    }
}

void Server::_receivePacketEvent(SocketEvent& event)
{
    Peer::Id peerId = event.peer.id();
    Player& player = _players[peerId];

    PacketReadStream stream = event.packet.readStream();
    uint8_t packetType = stream.readByte();

    size_t position = stream.position();

    switch (packetType)
    {
    case PacketType::Authorization:
    {
        std::string name = stream.readString();
        player.authorized = true;
        player.name = name;

        LOG_TRACE(format("Server: Peer '%d' authorized as '%s'", peerId, name.c_str()));
    } break;
    }

    for (ServerListener* listener : _listeners)
    {
        stream.seek(position);
        listener->receivePacket(player, (PacketType)packetType, stream);
    }
}

void Server::_sendAuthorizationRequest(Peer peer)
{
    LOG_TRACE(format("Server: Requesting peer '%d' to authorize", peer.id()));

    Packet packet(PacketFlag::Reliable);
    PacketWriteStream stream = packet.writeStream();
    stream.writeByte((uint8_t)PacketType::AuthorizationRequest);
    _socket.sendPacket(peer, 0, packet);
}