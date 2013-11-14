#include "ClientState.h"

ClientState::ClientState(Engine& engine) :
    State(engine, 1.0 / 60.0),
    _socket(IpAddress::localAddress(), 6006, 2)
{
}

void ClientState::update(double timeStep)
{
    UdpSocket::Event event;
    while (_socket.pollEvent(event))
    {
        switch (event.type)
        {
        case UdpSocket::Event::Connect:
            LOG_INFO(format("%s connected", event.address.toString().c_str()));
            break;
        case UdpSocket::Event::Disconnect:
            LOG_INFO(format("%s disconnected", event.address.toString().c_str()));
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