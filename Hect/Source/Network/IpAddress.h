namespace hect
{

///
/// An Internet Protocol address.
class IpAddress
{
public:
    
    ///
    /// Returns the local IP address.
    static IpAddress localAddress();

    ///
    /// Returns the public IP address.
    static IpAddress publicAddress();

    ///
    /// Constructs an IP address from a string.
    ///
    /// \param address A string representation of the address.
    IpAddress(const std::string& address);

    ///
    /// Constructs an IP address from a raw 32-bit value.
    ///
    /// \param address The 32-bit value of the address.
    IpAddress(uint32_t address);

    ///
    /// Returns a string representation of the address.
    std::string toString() const;

private:
    uint32_t _address;
};

}