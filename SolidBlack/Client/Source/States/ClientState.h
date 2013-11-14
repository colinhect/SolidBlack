#pragma once

#include <Hect.h>

using namespace hect;

class ClientState :
    public State,
    public Keyboard::Listener
{
public:
    ClientState(Engine& engine);

    void update(double timeStep);

    void notifyKeyboardEvent(const Keyboard::Event& event);

private:
    UdpSocket _socket;
};