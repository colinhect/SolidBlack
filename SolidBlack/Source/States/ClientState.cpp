#include "ClientState.h"

#include "PacketType.h"

ClientState::ClientState(Engine& engine) :
    State(engine, 1.0 / 60.0),
    _socket(1, 2)
{
    _server = _socket.connectToPeer(IpAddress::localAddress(), 6006);
}

ClientState::~ClientState()
{
    if (_server.state() == Peer::Connected)
    {
        _socket.disconnectFromPeer(_server);

        // Wait for the disconnect event
        Socket::Event event;
        while (_socket.pollEvent(event, TimeSpan::fromSeconds(3)))
        {
            if (event.type == Socket::Event::Disconnect)
            {
                break;
            }
        }
    }
}

void ClientState::update(double timeStep)
{
    Socket::Event event;
    while (_socket.pollEvent(event))
    {
        switch (event.type)
        {
        case Socket::Event::Connect:
            LOG_INFO("Connection established");
            break;
        case Socket::Event::Disconnect:
            LOG_INFO("Disconnection occurred");
            break;
        case Socket::Event::Receive:
            _receivePacketEvent(event);
            break;
        }
    }
}

void ClientState::notifyKeyboardEvent(const Keyboard::Event& event)
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

void ClientState::_receivePacketEvent(Socket::Event& event)
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

void ClientState::_sendAuthorization()
{
    static const std::string name("Colin");

    LOG_INFO(format("Sending authorization as \"%s\"", name.c_str()));

    Packet packet(Packet::Reliable);
    PacketWriteStream stream = packet.writeStream();
    stream.writeByte(PacketType::Authorization);
    stream.writeString(name);

    _socket.sendPacket(_server, 0, packet);
    _socket.flush();
}