namespace hect
{

///
/// A server which uses the User Datagram Protocol
class UdpServer
{
public:    
    UdpServer(uint16_t port, unsigned maxConnectionCount, unsigned channelCount);
    ~UdpServer();

    UdpEvent pollEvent(TimeSpan timeOut = TimeSpan::fromMilliseconds(0));

private:
    void* _host;
};

}