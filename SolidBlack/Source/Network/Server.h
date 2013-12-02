#pragma once

class Server :
    public Uncopyable
{
public:
    Server();

    void update(double timeStep);

private:
    void _connectionEvent(SocketEvent& event);
    void _disconnectionEvent(SocketEvent& event);
    void _receivePacketEvent(SocketEvent& event);
    void _sendAuthorizationRequest(Peer peer);

    enum
    {
        MaxPlayerCount = 128,
        Port = 6006,
        ChannelCount = 2
    };

    Socket _socket;
    Player _players[MaxPlayerCount];
};