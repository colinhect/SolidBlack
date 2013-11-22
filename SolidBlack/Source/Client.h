#pragma once

#include <Hect.h>
using namespace hect;

class Client :
    public Uncopyable
{
public:
    Client(IpAddress serverAddress, Port port);
    ~Client();

    void update();

private:
    void _receivePacketEvent(SocketEvent& event);
    void _sendAuthorization();

    Socket _socket;
    Peer _server;
};