#pragma once

#include <Hect.h>

using namespace hect;

class ServerState :
    public State,
    public Keyboard::Listener
{
public:
    ServerState(Engine& engine);

    void update(double timeStep);

    void notifyKeyboardEvent(const Keyboard::Event& event);

private:
    UdpSocket _socket;
};