namespace hect
{

class Connection
{
    friend class Socket;
public:
    typedef uint16_t SocketId;

    enum State
    {
        Disconnected,
        Connecting,
        AcknowledgingConnect,
        ConnectionPending,
        ConnectionSucceeded,
        Connected,
        DisconnectLater,
        Disconnecting,
        AcknowledgeDisconnect,
        Zombie,
        Invalid
    };

    Connection();

    SocketId incomingSocketId() const;
    SocketId outgoingSocketId() const;

    IpAddress address() const;
    State state() const;

private:
    void* _enetPeer;
};

}