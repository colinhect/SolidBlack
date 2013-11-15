#include "ClientState.h"

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
        Peer peer = event.peer;
        std::string address = peer.address().toString();

        switch (event.type)
        {
        case Socket::Event::Connect:
            LOG_INFO(format("[%d] Connect (%s)", peer.id(), address.c_str()));
            break;
        case Socket::Event::Disconnect:
            LOG_INFO(format("[%d] Disconnect (%s)", peer.id(), address.c_str()));
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