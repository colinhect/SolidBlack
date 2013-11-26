#pragma once

#include "Hect.h"
using namespace hect;

class DebugCamera :
    public Component<DebugCamera>
{
};

class DebugCameraSerializer :
    public ComponentSerializer<DebugCamera>
{
};