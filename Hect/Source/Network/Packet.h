#pragma once

namespace hect
{

///
/// A packet of data transported across a network connection.
class Packet
{
    friend class Socket;
public:

    ///
    /// A flag describing how a packet is transported.
    enum Flag
    {
        ///
        /// Packet must be received by the target peer and resend attempts
        /// should be made until the packet is delivered.
        Reliable = 1,

        ///
        /// Packet will not be sequenced with other packets.
        ///
        /// \warning Not supported for reliable packets.
        Unsequenced = 2
    };

    ///
    /// Constructs a packet given its flags.
    ///
    /// \param flags The flags describing how the packet is transported.
    Packet(uint8_t flags = 0);
    
    ///
    /// Returns a read stream for the packet data.
    MemoryReadStream readStream() const;

    ///
    /// Returns a write stream for the packet data.
    MemoryWriteStream writeStream();

private:
    Packet(const std::vector<uint8_t>& data);

    uint8_t _flags;
    std::vector<uint8_t> _data;
};

}