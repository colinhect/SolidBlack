#include "Hect.h"

using namespace hect;

#include <SFML/Network.hpp>

IpAddress IpAddress::localAddress()
{
    uint32_t address = sf::IpAddress::getLocalAddress().toInteger();
    return IpAddress(reverseBytes(address));
}

IpAddress IpAddress::publicAddress()
{
    uint32_t address = sf::IpAddress::getPublicAddress().toInteger();
    return IpAddress(reverseBytes(address));
}

IpAddress::IpAddress(const std::string& address) :
    _address(reverseBytes(sf::IpAddress(address).toInteger()))
{
}

IpAddress::IpAddress(uint32_t address) :
    _address(address)
{
}

bool IpAddress::isValid() const
{
    return _address != 0;
}

std::string IpAddress::toString() const
{
    return sf::IpAddress(_address).toString();
}

IpAddress::operator uint32_t() const
{
    return _address;
}