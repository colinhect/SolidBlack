#include "Hect.h"

using namespace hect;

#include <enet/enet.h>

Peer::Peer() :
    _enetPeer(nullptr)
{
}

Peer::Id Peer::id() const
{
    if (!_enetPeer)
    {
        return 0;
    }

    return ((ENetPeer*)_enetPeer)->incomingPeerID;
}

IpAddress Peer::address() const
{
    if (!_enetPeer)
    {
        return IpAddress(0);
    }

    uint32_t address = ((ENetPeer*)_enetPeer)->address.host;
    address = reverseBytes(address);

    return IpAddress(address);
}

Peer::State Peer::state() const
{
    if (!_enetPeer)
    {
        return Disconnected;
    }

    return (State)((ENetPeer*)_enetPeer)->state;
}

bool Peer::operator==(const Peer& peer) const
{
    return _enetPeer == peer._enetPeer;
}