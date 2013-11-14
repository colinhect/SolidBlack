#include "Hect.h"

using namespace hect;

#include <enet/enet.h>

Client::Event::Event() :
    type(None)
{
}

Client::Client(const IpAddress& serverAddress, uint16_t port, unsigned channelCount) :
    _host(nullptr),
    _peer(nullptr),
    _serverAddress(serverAddress),
    _port(port),
    _connected(false)
{
    _host = enet_host_create(0, 1, channelCount, 0, 0);
    if (!_host)
    {
        throw Error("Failed to create network client");
    }

    ENetAddress address;
    enet_address_set_host(&address, serverAddress.toString().c_str());
    address.port = port;

    _peer = enet_host_connect((ENetHost*)_host, &address, channelCount, 0);
    if (!_peer)
    {
        throw Error("Failed to create network peer");
    }
}

Client::~Client()
{
    if (_connected)
    {
        enet_peer_disconnect((ENetPeer*)_peer, 0);

        ENetEvent event;
        while (_connected && enet_host_service((ENetHost*)_host, &event, 5000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
            break;
            case ENET_EVENT_TYPE_DISCONNECT:
                _connected = false;
                break;
            }
        }

        enet_peer_reset((ENetPeer*)_peer);
    }
    if (_host)
    {
        enet_host_destroy((ENetHost*)_host);
        _host = nullptr;
    }
}

bool Client::isConnected() const
{
    return _connected;
}

Client::Event Client::pollEvent(TimeSpan timeOut)
{
    ENetEvent enetEvent;
    if (enet_host_service((ENetHost*)_host, &enetEvent, (uint32_t)timeOut.milliseconds()) > 0)
    {
        Event event;
        switch (enetEvent.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            _connected = true;
            event.type = Event::Connect;
            return event;
        case ENET_EVENT_TYPE_DISCONNECT:
            _connected = false;
            event.type = Event::Disconnect;
            return event;
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(enetEvent.packet);
        break;
        }
    }

    return Event();
}