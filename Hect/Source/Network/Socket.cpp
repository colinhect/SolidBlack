#include "Hect.h"

using namespace hect;

#include <enet/enet.h>

Socket::Event::Event() :
    type(None)
{
}

Socket::Socket(unsigned maxConnectionCount, unsigned channelCount) :
    _enetHost(nullptr)
{
    _enetHost = enet_host_create(nullptr, maxConnectionCount, channelCount, 0, 0);
    if (!_enetHost)
    {
        throw Error("Failed to create UDP socket");
    }
}

Socket::Socket(uint16_t port, unsigned maxConnectionCount, unsigned channelCount) :
    _enetHost(nullptr)
{
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;
    _enetHost = enet_host_create(&address, maxConnectionCount, channelCount, 0, 0);
    if (!_enetHost)
    {
        throw Error("Failed to create UDP socket");
    }
}

Socket::~Socket()
{
    if (_enetHost)
    {
        enet_host_destroy((ENetHost*)_enetHost);
        _enetHost = nullptr;
    }
}

Connection Socket::connect(IpAddress address, uint16_t port)
{
    ENetAddress enetAddress;
    enetAddress.host = reverseBytes(address.toInteger());
    enetAddress.port = port;

    ENetPeer* enetPeer = enet_host_connect((ENetHost*)_enetHost, &enetAddress, ((ENetHost*)_enetHost)->channelLimit, 0);
    if (!enetPeer)
    {
        throw Error("Failed to create UDP connection");
    }

    Connection peer;
    peer._enetPeer = enetPeer;

    return peer;
}

void Socket::disconnect(const Connection& peer)
{
    ENetPeer* enetPeer = (ENetPeer*)peer._enetPeer;
    if (peer.state() == Connection::Connected)
    {
        enet_peer_disconnect(enetPeer, 0);

        bool disconnectEvent = false;
        Socket::Event event;
        while (!disconnectEvent && pollEvent(event, TimeSpan::fromSeconds(1)))
        {
            switch (event.type)
            {
            case Socket::Event::Disconnect:
                disconnectEvent = true;
                break;
            }
        }

        enet_peer_reset(enetPeer);
    }
}

bool Socket::pollEvent(Event& event, TimeSpan timeOut)
{
    ENetEvent enetEvent;
    if (enet_host_service((ENetHost*)_enetHost, &enetEvent, (uint32_t)timeOut.milliseconds()) > 0)
    {
        event.type = (Event::Type)enetEvent.type;
        event.connection._enetPeer = enetEvent.peer;

        switch (enetEvent.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(enetEvent.packet);
        break;
        }

        return true;
    }

    return false;
}