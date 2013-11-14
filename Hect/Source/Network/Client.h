namespace hect
{

class Client
{
public:
    class Event
    {
        friend class Client;
    public:
        Event();

        enum Type
        {
            None,
            Connect,
            Disconnect
        };

        Type type;
    };

    Client(const IpAddress& serverAddress, uint16_t port, unsigned channelCount);
    ~Client();
    
    bool isConnected() const;
    
    Event pollEvent(TimeSpan timeOut = TimeSpan::fromMilliseconds(0));

private:
    void* _host;
    void* _peer;

    IpAddress _serverAddress;
    uint16_t _port;
    bool _connected;
};

}