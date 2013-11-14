#include "Hect.h"

using namespace hect;

#include <enet/enet.h>

UdpServer::UdpServer(uint16_t port, unsigned maxClientCount, unsigned channelCount) :
    _host(nullptr)
{
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;
    _host = enet_host_create(&address, maxClientCount, channelCount, 0, 0);
    if (!_host)
    {
        throw Error("Failed to create network server");
    }
}

UdpServer::~UdpServer()
{
    if (_host)
    {
        enet_host_destroy((ENetHost*)_host);
        _host = nullptr;
    }
}

UdpEvent UdpServer::pollEvent(TimeSpan timeOut)
{
    ENetEvent enetEvent;
    if (enet_host_service((ENetHost*)_host, &enetEvent, (uint32_t)timeOut.milliseconds()) > 0)
    {
        UdpEvent event;
        switch (enetEvent.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            event.type = UdpEvent::Connect;
            event.address = IpAddress(reverseBytes(enetEvent.peer->address.host));
            return event;
        case ENET_EVENT_TYPE_DISCONNECT:
            event.type = UdpEvent::Disconnect;
            event.address = IpAddress(reverseBytes(enetEvent.peer->address.host));
            return event;
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(enetEvent.packet);
        break;
        }
    }

    return UdpEvent();
}