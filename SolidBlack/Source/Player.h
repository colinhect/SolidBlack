#pragma once

#include <Hect.h>
using namespace hect;

class Player
{
public:
    Player();

    std::string name;
    Peer peer;
    bool authorized;
};