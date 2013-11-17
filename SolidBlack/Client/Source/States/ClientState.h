#pragma once

#include <Hect.h>

using namespace hect;

class ClientState :
    public State,
    public Keyboard::Listener
{
public:
    ClientState(Engine& engine);
    ~ClientState();

    void update(double timeStep);

    void notifyKeyboardEvent(const Keyboard::Event& event);

private:
    void _receivePacketEvent(Socket::Event& event);

    void _sendAuthorization();

    Socket _socket;
    Peer _server;
};