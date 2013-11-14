#include "Hect.h"

using namespace hect;

#include <enet/enet.h>

Client::Event::Event() :
    type(None)
{
}

Client::Client(unsigned channelCount) :
    _host(nullptr),
    _peer(nullptr),
    _connected(false)
{
    _host = enet_host_create(0, 1, channelCount, 0, 0);
    if (!_host)
    {
        throw Error("Failed to create network client");
    }
}

Client::~Client()
{
    if (_connected)
    {
        disconnect(TimeSpan::fromSeconds(5));
    }
    if (_host)
    {
        enet_host_destroy((ENetHost*)_host);
        _host = nullptr;
    }
}

bool Client::connect(const IpAddress& serverAddress, uint16_t port, TimeSpan timeOut)
{
    if (_connected)
    {
        throw Error("The client is already connected");
    }

    ENetAddress address;
    address.host = serverAddress.toInteger();
    address.port = port;

    _peer = enet_host_connect((ENetHost*)_host, &address, ((ENetHost*)_host)->channelLimit, 0);
    if (!_peer)
    {
        return false;
    }
    
    ENetEvent event;
    if (enet_host_service((ENetHost*)_host, &event, (uint32_t)timeOut.milliseconds()) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        _connected = true;
        return true;
    }
    else
    {
        enet_peer_reset((ENetPeer*)_peer);
        _peer = nullptr;

        return false;
    }
}

bool Client::disconnect(TimeSpan timeOut)
{
    if (!_connected)
    {
        throw Error("The client is not connected");
    }
    _connected = false;
    
    enet_peer_disconnect((ENetPeer*)_peer, 0);

    ENetEvent event;
    while (enet_host_service((ENetHost*)_host, &event, (uint32_t)timeOut.milliseconds()) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(event.packet);
        break;
        case ENET_EVENT_TYPE_DISCONNECT:
            return true;
        }
    }

    enet_peer_reset((ENetPeer*)_peer);
    return false;
}

bool Client::isConnected() const
{
    return _connected;
}

Client::Event Client::pollEvent(TimeSpan timeOut)
{
    if (!_connected)
    {
        throw Error("The client is not connected");
    }

    ENetEvent enetEvent;
    if (enet_host_service((ENetHost*)_host, &enetEvent, (uint32_t)timeOut.milliseconds()) > 0)
    {
        Event event;
        switch (enetEvent.type)
        {
        case ENET_EVENT_TYPE_DISCONNECT:
            event.type = Event::Disconnect;
            return event;
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(enetEvent.packet);
        break;
        }
    }

    return Event();
}