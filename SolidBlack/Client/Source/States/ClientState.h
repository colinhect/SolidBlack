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
    Socket _socket;
    Peer _server;
};