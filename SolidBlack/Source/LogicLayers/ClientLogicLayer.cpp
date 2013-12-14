#include "SolidBlack.h"

ClientLogicLayer::ClientLogicLayer(IpAddress serverAddress, Port port) :
    _socket(1, 2)
{
    _server = _socket.connectToPeer(serverAddress, port);
}

ClientLogicLayer::~ClientLogicLayer()
{
    if (_server.state() == PeerState::Connected)
    {
        _socket.disconnectFromPeer(_server);

        // Wait for the disconnect event
        SocketEvent event;
        while (_socket.pollEvent(event, TimeSpan::fromSeconds(0.5)))
        {
            if (event.type == SocketEventType::Disconnect)
            {
                break;
            }
        }
    }
}

void ClientLogicLayer::fixedUpdate(double timeStep)
{
    timeStep;

    SocketEvent event;
    while (_socket.pollEvent(event))
    {
        switch (event.type)
        {
        case SocketEventType::Connect:
            LOG_INFO("Connection established");
            break;
        case SocketEventType::Disconnect:
            LOG_INFO("Disconnection occurred");
            break;
        case SocketEventType::Receive:
            _receivePacketEvent(event);
            break;
        }
    }
}

void ClientLogicLayer::frameUpdate(double delta)
{
    delta;
}

void ClientLogicLayer::_receivePacketEvent(SocketEvent& event)
{
    PacketReadStream stream = event.packet.readStream();

    uint8_t packetType = stream.readByte();
    switch (packetType)
    {
    case PacketType::AuthorizationRequest:
        _sendAuthorization();
        break;
    }
}

void ClientLogicLayer::_sendAuthorization()
{
    static const std::string name("Colin");

    LOG_INFO(format("Sending authorization as \"%s\"", name.c_str()));

    Packet packet(PacketFlag::Reliable);
    PacketWriteStream stream = packet.writeStream();
    stream.writeByte((uint8_t)PacketType::Authorization);
    stream.writeString(name);

    _socket.sendPacket(_server, 0, packet);
    _socket.flush();
}