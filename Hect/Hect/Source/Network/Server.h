namespace hect
{

class Server
{
public:
    class Event
    {
        friend class Server;
    public:
        Event();

        enum Type
        {
            None,
            Connect,
            Disconnect
        };

        Type type;
        IpAddress clientAddress;
    };

    Server(uint16_t port, unsigned maxClientCount, unsigned channelCount);
    ~Server();

    Event pollEvent(TimeSpan timeOut = TimeSpan::fromMilliseconds(0));

private:
    void* _host;
};

}