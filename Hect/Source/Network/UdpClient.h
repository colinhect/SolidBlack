namespace hect
{

class UdpClient
{
public:
    UdpClient(const IpAddress& serverAddress, uint16_t port, unsigned channelCount);
    ~UdpClient();
    
    bool isConnected() const;
    
    UdpEvent pollEvent(TimeSpan timeOut = TimeSpan::fromMilliseconds(0));

private:
    void* _host;
    void* _peer;

    IpAddress _serverAddress;
    uint16_t _port;
    bool _connected;
};

}