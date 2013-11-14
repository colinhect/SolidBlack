namespace hect
{

class UdpEvent
{
public:
    UdpEvent();

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

}