namespace hect
{

class Socket :
    public Uncopyable
{
    friend class Connection;
public:
    class Event
    {
    public:
        Event();

        enum Type
        {
            None = 0,
            Connect,
            Disconnect,
            Receive
        };

        Type type;
        Connection connection;
    };
    
    ///
    /// Constructs a socket which does not listen for incoming connections.
    Socket(unsigned maxConnectionCount, unsigned channelCount);
    
    ///
    /// Constructs a socket which listens for connections on a given port.
    Socket(uint16_t port, unsigned maxConnectionCount, unsigned channelCount);
    ~Socket();

    Connection connect(IpAddress address, uint16_t port);
    void disconnect(const Connection& peer);

    bool pollEvent(Event& event, TimeSpan timeOut = TimeSpan::fromMilliseconds(0));

private:
    void* _enetHost;
};

}