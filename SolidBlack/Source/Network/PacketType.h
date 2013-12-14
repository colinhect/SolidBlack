#pragma once

enum class PacketType
{
    AuthorizationRequest,
    Authorization,

    ClearScene,
    CreateEntity,
    DestroyEntity
};