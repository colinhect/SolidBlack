#pragma once

class ServerListener
{
public:
    virtual void receivePacket(const Player& player, PacketType type, PacketReadStream& stream);
};

class Server :
    public Uncopyable
{
public:
    Server();

    void addListener(ServerListener& listener);
    void removeListener(ServerListener& listener);

    void refresh();

    Socket& socket();

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

    std::vector<ServerListener*> _listeners;
};