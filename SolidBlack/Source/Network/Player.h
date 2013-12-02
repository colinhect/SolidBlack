#pragma once

class Player
{
public:
    Player();

    std::string name;
    Peer peer;
    bool authorized;
};