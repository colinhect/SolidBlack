#pragma once

class ServerListener
{
public:
    virtual void receivePacket(const Player& player, PacketType type, PacketReadStream& stream);
};