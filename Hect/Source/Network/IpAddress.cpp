#include "Hect.h"

using namespace hect;

#include <SFML/Network.hpp>

IpAddress IpAddress::localAddress()
{
    uint32_t address = sf::IpAddress::getLocalAddress().toInteger();
    return IpAddress(address);
}

IpAddress IpAddress::publicAddress()
{
    uint32_t address = sf::IpAddress::getPublicAddress().toInteger();
    return IpAddress(address);
}

IpAddress::IpAddress(const std::string& address) :
    _address(sf::IpAddress(address).toInteger())
{
}

IpAddress::IpAddress(uint32_t address) :
    _address(address)
{
}

std::string IpAddress::toString() const
{
    return sf::IpAddress(_address).toString();
}