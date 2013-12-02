#pragma once

namespace hect
{

///
/// A state that a peer is in.
enum class PeerState
{
    ///
    /// Not connected.
    Disconnected,

    ///
    /// Connection in progress.
    Connecting,

    ///
    /// Acknowledgement of connection receieved.
    AcknowledgingConnect,

    ///
    /// Connection pending.
    ConnectionPending,

    ///
    /// Connection succeeded.
    ConnectionSucceeded,

    ///
    /// Connection fully established.
    Connected,

    ///
    /// Disconnection will triggered.
    DisconnectLater,

    ///
    /// Disconnection in progress.
    Disconnecting,

    ///
    /// Acknowledgement of disconnection receieved.
    AcknowledgeDisconnect,

    ///
    /// Unknown state.
    Unknown
};


///
/// A remote point of contact for remote communication over UDP.
///
/// \remarks Peers are lightweight handles.  Copying a peer will copy the
/// the handle and they will both refer to the same peer.  Peers are created
/// and destroyed from a socket and are provided in socket events.
class Peer
{
    friend class Socket;
public:

    ///
    /// A locally unique id for a peer.
    typedef uint16_t Id;

    ///
    /// Constructs an invalid peer.
    Peer();

    ///
    /// Returns the locally unique id of the peer.
    Id id() const;

    ///
    /// Returns the remote address of the peer.
    IpAddress address() const;

    ///
    /// Returns the current state of the peer.
    PeerState state() const;

    bool operator==(const Peer& peer) const;

private:
    void* _enetPeer;
};

}