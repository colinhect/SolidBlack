#include "Hect.h"

using namespace hect;

#include <enet/enet.h>

Connection::Connection() :
    _enetPeer(nullptr)
{
}

Connection::SocketId Connection::incomingSocketId() const
{
    if (!_enetPeer)
    {
        return 0;
    }

    return ((ENetPeer*)_enetPeer)->incomingPeerID;
}

Connection::SocketId Connection::outgoingSocketId() const
{
    if (!_enetPeer)
    {
        return 0;
    }

    return ((ENetPeer*)_enetPeer)->outgoingPeerID;
}

IpAddress Connection::address() const
{
    if (!_enetPeer)
    {
        return IpAddress(0);
    }

    return IpAddress(reverseBytes(((ENetPeer*)_enetPeer)->address.host));
}

Connection::State Connection::state() const
{
    if (!_enetPeer)
    {
        return Invalid;
    }
    
    return (State)((ENetPeer*)_enetPeer)->state;
}