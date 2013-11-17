#pragma once

#include <Hect.h>
using namespace hect;

class PacketType
{
public:
    enum Id :
        uint8_t
    {
        AuthorizationRequest,
        Authorization
    };
};