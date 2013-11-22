#pragma once

#include "Hect.h"
using namespace hect;

class FreeCameraController :
    public Component<FreeCameraController>
{
};

class FreeCameraControllerSerializer :
    public ComponentSerializer<FreeCameraController>
{
};