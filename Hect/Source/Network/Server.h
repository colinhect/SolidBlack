namespace hect
{

class Server
{
public:
    class Event
    {
        friend class Server;
    public:

        enum Type
        {
            None,
            Connect,
            Disconnect
        };

        Type type;
        IpAddress clientAddress;

    private:
        Event();
    };

    Server(uint16_t port, unsigned maxClientCount, unsigned channelCount);
    ~Server();

    Event pollEvent(TimeSpan timeOut = TimeSpan::fromMilliseconds(0));

private:
    void* _host;
};

}