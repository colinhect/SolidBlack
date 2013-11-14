namespace hect
{

class UdpSocket :
    public Uncopyable
{
public:
    class Event
    {
    public:
        Event();

        enum Type
        {
            None,
            Connect,
            Disconnect,
            Receive
        };

        Type type;
        IpAddress address;
    };

    UdpSocket(uint16_t port, unsigned maxConnectionCount, unsigned channelCount);
    UdpSocket(const IpAddress& address, uint16_t port, unsigned channelCount);
    ~UdpSocket();

    bool pollEvent(Event& event, TimeSpan timeOut = TimeSpan::fromMilliseconds(0));

private:
    void* _host;
    void* _peer;
};

}