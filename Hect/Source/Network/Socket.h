#pragma once

namespace hect
{

///
/// An Internet Protocol port.
typedef uint16_t Port;

///
/// An event type.
enum class SocketEventType
{
    ///
    /// No event occurred.
    None = 0,

    ///
    /// A connection to a peer has been established.
    Connect,

    ///
    /// A connection to a peer has been lost.
    Disconnect,

    ///
    /// A packet has been received from a peer.
    Receive
};

///
/// An event triggered from a remote socket.
class SocketEvent
{
public:

    ///
    /// Constructs a blank event.
    SocketEvent();

    ///
    /// The event type.
    SocketEventType type;

    ///
    /// The remote socket triggering the event.
    Peer peer;

    ///
    /// The packet received (only for events with type
    /// Socket::Event::Receive).
    Packet packet;
};

///
/// A local point of contact for remote communication over UDP.
///
/// \remarks A socket can either listen for incoming connections or attempt
/// to connect to a remote socket which is listening.
class Socket :
    public Uncopyable
{
public:

    ///
    /// Constructs a socket which does not listen for incoming connections.
    ///
    /// \param maxConnectionCount The maximum number of simultaneous outgoing
    /// connections the socket can create.
    /// \param channelCount The number of channels to use.
    Socket(unsigned maxConnectionCount, uint8_t channelCount);

    ///
    /// Constructs a socket which listens for incoming connections on a given
    /// port.
    ///
    /// \param port The port to listen on.
    /// \param maxConnectionCount The maximum number of simultaneous incoming
    /// connections the socket can accept.
    /// \param channelCount The number of channels to use.
    Socket(Port port, unsigned maxConnectionCount, uint8_t channelCount);

    ///
    /// Destroys the socket.
    ~Socket();

    ///
    /// Triggers a connection handshake attempt with a remote socket.
    ///
    /// \remarks Although a peer is always returned successfully, the
    /// connection to that peer may or may not successfully establish.  If the
    /// connection succeeds then an event will be received and the peer's state
    /// will change to Peer::Connected.
    ///
    /// \param address The address of the remote socket.
    /// \param port The port the remote socket is listening on.
    Peer connectToPeer(IpAddress address, Port port);

    ///
    /// Triggers a disconnection handshake attempt with a remote socket.
    ///
    /// \remarks If a connection to the peer is not established then nothing
    /// happens.
    ///
    /// \param peer The peer.
    void disconnectFromPeer(Peer peer);

    ///
    /// Polls the next event triggered from a remote socket.
    ///
    /// \param event The event.
    /// \param timeOut The time span to wait for an event to occur.
    ///
    /// \returns True if an event was received; false otherwise.
    bool pollEvent(SocketEvent& event, TimeSpan timeOut = TimeSpan::fromMilliseconds(0));

    ///
    /// Sends a packet to a remote socket.
    ///
    /// \remarks The packet is not sent instantaneously.  It will eventually
    /// occur during a call to pollEvent() or can be forced by calling flush().
    ///
    /// \param peer The peer to receive the packet.
    /// \param channel The channel to send the packet on.
    /// \param packet The packet to send.
    void sendPacket(Peer peer, uint8_t channel, const Packet& packet);

    ///
    /// Broadcasts a packet to all connected remote sockets.
    ///
    /// \remarks The packet is not sent instantaneously.  It will eventually
    /// occur during a call to pollEvent() or can be forced by calling flush().
    ///
    /// \param channel The channel to send the packet on.
    /// \param packet The packet to send.
    void broadcastPacket(uint8_t channel, const Packet& packet);

    ///
    /// Force any enqueued packet transmissions to occur.
    void flush();

private:
    void* _enetHost;
    std::vector<Peer> _peers;
};

}