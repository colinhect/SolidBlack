#include "Hect.h"

using namespace hect;

#include <enet/enet.h>

int _enetInitializationCounter = 0;

Socket::Event::Event() :
    type(None)
{
}

Socket::Socket(unsigned maxConnectionCount, uint8_t channelCount) :
    _enetHost(nullptr)
{
    if (_enetInitializationCounter == 0)
    {
        ++_enetInitializationCounter;
        if (enet_initialize() != 0)
        {
            throw Error("Failed to initialized ENet");
        }
    }

    _enetHost = enet_host_create(nullptr, maxConnectionCount, channelCount, 0, 0);
    if (!_enetHost)
    {
        throw Error("Failed to create socket");
    }
}

Socket::Socket(uint16_t port, unsigned maxConnectionCount, uint8_t channelCount) :
    _enetHost(nullptr)
{
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;
    _enetHost = enet_host_create(&address, maxConnectionCount, channelCount, 0, 0);
    if (!_enetHost)
    {
        throw Error("Failed to create socket");
    }
}

Socket::~Socket()
{
    if (_enetHost)
    {
        enet_host_destroy((ENetHost*)_enetHost);
        _enetHost = nullptr;
    }

    if (_enetInitializationCounter != 0)
    {
        --_enetInitializationCounter;
        enet_deinitialize();
    }
}

Peer Socket::connectToPeer(IpAddress address, uint16_t port)
{
    ENetAddress enetAddress;
    enetAddress.host = reverseBytes(address.toInteger());
    enetAddress.port = port;

    ENetPeer* enetPeer = enet_host_connect((ENetHost*)_enetHost, &enetAddress, ((ENetHost*)_enetHost)->channelLimit, 0);
    if (!enetPeer)
    {
        throw Error("Failed to create peer");
    }

    Peer peer;
    peer._enetPeer = enetPeer;

    _peers.push_back(peer);

    return peer;
}

void Socket::disconnectFromPeer(Peer peer)
{
    // Ensure the peer belongs to this socket
    if (std::find(_peers.begin(), _peers.end(), peer) == _peers.end())
    {
        return;
    }

    // Remove the peer
    _peers.erase(std::remove(_peers.begin(), _peers.end(), peer), _peers.end());

    // Trigger the disconnect
    ENetPeer* enetPeer = (ENetPeer*)peer._enetPeer;
    if (peer.state() == Peer::Connected)
    {
        enet_peer_disconnect(enetPeer, 0);
    }
    else
    {
        enet_peer_reset(enetPeer);
    }
}

bool Socket::pollEvent(Event& event, TimeSpan timeOut)
{
    ENetEvent enetEvent;
    if (enet_host_service((ENetHost*)_enetHost, &enetEvent, (uint32_t)timeOut.milliseconds()) > 0)
    {
        event.type = (Event::Type)enetEvent.type;
        event.peer._enetPeer = enetEvent.peer;

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

void Socket::sendPacket(Peer peer, uint8_t channel, const Packet& packet)
{

}

void Socket::broadcastPacket(uint8_t channel, const Packet& packet)
{
}

void Socket::flush()
{
    enet_host_flush((ENetHost*)_enetHost);
}