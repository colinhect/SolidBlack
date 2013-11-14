#include "Hect.h"

using namespace hect;

#include <enet/enet.h>

UdpSocket::Event::Event() :
    type(None),
    address(0)
{
}

UdpSocket::UdpSocket(uint16_t port, unsigned maxConnectionCount, unsigned channelCount) :
    _host(nullptr),
    _peer(nullptr)
{
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;
    _host = enet_host_create(&address, maxConnectionCount, channelCount, 0, 0);
    if (!_host)
    {
        throw Error("Failed to create UDP socket");
    }
}

UdpSocket::UdpSocket(const IpAddress& serverAddress, uint16_t port, unsigned channelCount) :
    _host(nullptr),
    _peer(nullptr)
{
    _host = enet_host_create(0, 1, channelCount, 0, 0);
    if (!_host)
    {
        throw Error("Failed to create UDP socket");
    }

    ENetAddress address;
    enet_address_set_host(&address, serverAddress.toString().c_str());
    address.port = port;

    _peer = enet_host_connect((ENetHost*)_host, &address, channelCount, 0);
    if (!_peer)
    {
        throw Error("Failed to attempt UDP connection");
    }
}

UdpSocket::~UdpSocket()
{
    if (_peer && ((ENetPeer*)_peer)->state == ENET_PEER_STATE_CONNECTED)
    {
        enet_peer_disconnect((ENetPeer*)_peer, 0);

        bool disconnectEvent = false;
        ENetEvent event;
        while (!disconnectEvent && enet_host_service((ENetHost*)_host, &event, 5000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
            break;
            case ENET_EVENT_TYPE_DISCONNECT:
                disconnectEvent = true;
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

bool UdpSocket::pollEvent(Event& event, TimeSpan timeOut)
{
    ENetEvent enetEvent;
    if (enet_host_service((ENetHost*)_host, &enetEvent, (uint32_t)timeOut.milliseconds()) > 0)
    {
        switch (enetEvent.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            event.type = Event::Connect;
            event.address = IpAddress(reverseBytes(enetEvent.peer->address.host));
            return true;
        case ENET_EVENT_TYPE_DISCONNECT:
            event.type = Event::Disconnect;
            event.address = IpAddress(reverseBytes(enetEvent.peer->address.host));
            return true;
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(enetEvent.packet);
        break;
        }
    }

    return false;
}