#include "ServerState.h"

ServerState::ServerState(Engine& engine) :
    State(engine, 1.0 / 60.0),
    _socket(6006, 256, 2)
{
}

void ServerState::update(double timeStep)
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