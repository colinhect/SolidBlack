#include "Hect.h"

using namespace hect;

#include <enet/enet.h>

Server::Event::Event() :
    type(None),
    clientAddress(0)
{
}

Server::Server(uint16_t port, unsigned maxClientCount, unsigned channelCount) :
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

Server::~Server()
{
    if (_host)
    {
        enet_host_destroy((ENetHost*)_host);
        _host = nullptr;
    }
}

Server::Event Server::pollEvent(TimeSpan timeOut)
{
    ENetEvent enetEvent;
    if (enet_host_service((ENetHost*)_host, &enetEvent, (uint32_t)timeOut.milliseconds()) > 0)
    {
        Event event;
        switch (enetEvent.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            event.type = Event::Connect;
            event.clientAddress = IpAddress(enetEvent.peer->address.host);
            return event;
        case ENET_EVENT_TYPE_DISCONNECT:
            event.type = Event::Disconnect;
            event.clientAddress = IpAddress(enetEvent.peer->address.host);
            return event;
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(enetEvent.packet);
        break;
        }
    }

    return Event();
}