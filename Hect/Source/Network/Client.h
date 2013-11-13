namespace hect
{

class Client
{
public:
    class Event
    {
        friend class Client;
    public:

        enum Type
        {
            None,
            Disconnect
        };

        Type type;

    private:
        Event();
    };

    Client(unsigned channelCount);
    ~Client();

    bool connect(const IpAddress& serverAddress, uint16_t port, TimeSpan timeOut);
    bool disconnect(TimeSpan timeOut);

    bool isConnected() const;
    
    Event pollEvent(TimeSpan timeOut = TimeSpan::fromMilliseconds(0));

private:
    void* _host;
    void* _peer;

    bool _connected;
};

}