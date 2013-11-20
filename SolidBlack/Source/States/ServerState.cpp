#include "ServerState.h"

#include "PacketType.h"
#include "Components/FreeCameraController.h"

ServerState::ServerState(Engine& engine) :
    SolidBlackState(engine, 1.0 / 30.0),
    _assetCache(engine.storage()),
    _socket(Port, MaxPlayerCount, ChannelCount)
{
    _bubbles.push_back(Bubble::Ref(new Bubble()));
}

void ServerState::begin()
{
    SolidBlackState::begin();
}

void ServerState::end()
{
    SolidBlackState::end();
}

void ServerState::update(double timeStep)
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

    for (const Bubble::Ref& bubble : _bubbles)
    {
        bubble->update(timeStep);
    }
}

void ServerState::render(double delta)
{
    engine().swapBuffers();
}

void ServerState::notifyKeyboardEvent(const Keyboard::Event& event)
{
    if (event.type != Keyboard::Event::KeyDown)
    {
        return;
    }

    if (event.key == Keyboard::Esc)
    {
        setActive(false);
    }
}

void ServerState::_connectionEvent(SocketEvent& event)
{
    Peer::Id peerId = event.peer.id();
    LOG_INFO(format("Connection (peerId  = %d)", peerId));

    Player& player = _players[peerId];
    if (player.authorized)
    {
        LOG_INFO("Player is already authorized");
    }
    else
    {
        _sendAuthorizationRequest(event.peer);
    }
}

void ServerState::_disconnectionEvent(SocketEvent& event)
{
    Peer::Id peerId = event.peer.id();
    Player& player = _players[peerId];
    if (player.authorized)
    {
        LOG_INFO(format("Player \"%s\" disconnected (peerId  = %d)", player.name.c_str(), peerId));
        player.authorized = false;
        player.name = "";
    }
    else
    {
        LOG_INFO(format("Unauthorized player disconnected (peerId  = %d)", peerId));
    }
}

void ServerState::_receivePacketEvent(SocketEvent& event)
{
    Peer::Id peerId = event.peer.id();
    Player& player = _players[peerId];

    PacketReadStream stream = event.packet.readStream();
    uint8_t packetType = stream.readByte();

    switch (packetType)
    {
    case PacketType::Authorization: {
            std::string name = stream.readString();
            player.authorized = true;
            player.name = name;

            LOG_INFO(format("Player authorized as \"%s\" (peerId  = %d)", name.c_str(), peerId));
        } break;
    }
}

void ServerState::_sendAuthorizationRequest(Peer peer)
{
    LOG_INFO("Requesting player authorization");

    Packet packet(PacketFlag::Reliable);
    PacketWriteStream stream = packet.writeStream();
    stream.writeByte(PacketType::AuthorizationRequest);
    _socket.sendPacket(peer, 0, packet);
    _socket.flush();
}