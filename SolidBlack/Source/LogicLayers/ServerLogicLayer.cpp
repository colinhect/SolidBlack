#include "SolidBlack.h"

ServerLogicLayer::ServerLogicLayer(AssetCache& assetCache) :
    _socket(Port, MaxPlayerCount, ChannelCount),
    _scene(),
    _proxySystem(_scene, assetCache, _socket)
{
    assetCache;
    _scene.registerComponent<DebugCamera, DebugCameraSerializer>("DebugCamera");
    _scene.registerComponent<Proxy, ProxySerializer>("Proxy");

    _scene.addSystem(_proxySystem);
    _scene.addSystem(_physicsSystem);

    {
        DataValue::Ref sceneValue = assetCache.get<DataValue>("Test.scene");
        _scene.load(*sceneValue, assetCache);
    }

    _scene.refresh();
}

void ServerLogicLayer::fixedUpdate(double timeStep)
{
    timeStep;

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

    _scene.refresh();
}

void ServerLogicLayer::_connectionEvent(SocketEvent& event)
{
    Peer::Id peerId = event.peer.id();
    LOG_INFO(format("Connection (peerId  = %d)", peerId));

    Player& player = _players[peerId];
    player.peer = event.peer;

    if (player.authorized)
    {
        LOG_INFO("Player is already authorized");
    }
    else
    {
        _sendAuthorizationRequest(event.peer);
    }
}

void ServerLogicLayer::_disconnectionEvent(SocketEvent& event)
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

void ServerLogicLayer::_receivePacketEvent(SocketEvent& event)
{
    Peer::Id peerId = event.peer.id();
    Player& player = _players[peerId];

    PacketReadStream stream = event.packet.readStream();
    uint8_t packetType = stream.readByte();

    switch (packetType)
    {
    case PacketType::Authorization:
    {
        std::string name = stream.readString();
        player.authorized = true;
        player.name = name;

        LOG_INFO(format("Player authorized as \"%s\" (peerId  = %d)", name.c_str(), peerId));

        _proxySystem.broadcastAll(player.peer);
    }
    break;
    }
}

void ServerLogicLayer::_sendAuthorizationRequest(Peer peer)
{
    LOG_INFO("Requesting player authorization");

    Packet packet(PacketFlag::Reliable);
    PacketWriteStream stream = packet.writeStream();
    stream.writeByte((uint8_t)PacketType::AuthorizationRequest);
    _socket.sendPacket(peer, 0, packet);
    _socket.flush();
}