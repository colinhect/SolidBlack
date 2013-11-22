#pragma once

#include <cstdint>

enum class PacketType :
    uint8_t
{
    AuthorizationRequest,
    Authorization
};