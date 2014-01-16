#pragma once

#include <Hect.h>
using namespace hect;

class PlayerCamera :
    public Component<PlayerCamera>
{
};

class PlayerCameraSerializer :
    public ComponentSerializer<PlayerCamera>
{
};