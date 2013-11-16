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

    return IpAddress(((ENetPeer*)_enetPeer)->address.host);
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