namespace hect
{

///
/// A packet of data transported across a network connection.
class Packet
{
public:

    ///
    /// Raw data of a packet.
    typedef std::vector<uint8_t> Data;

    ///
    /// A flag describing how a packet is transported.
    enum Flag
    {
        ///
        /// Packet must be received by the target peer and resend attempts
        /// should be made until the packet is delivered.
        ///
        /// \remarks Enabled by default.
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
    Packet(uint8_t flags = Reliable);

    ///
    /// Returns whether the packet has a given flag.
    ///
    /// \param flag The flag.
    bool hasFlag(Flag flag) const;

    ///
    /// Returns the raw packet data.
    Data& data();

    ///
    /// Returns the raw packet data.
    const Data& data() const;

private:
    uint8_t _flags;
    Data _data;
};

}