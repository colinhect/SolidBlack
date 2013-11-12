#pragma once

#include "States/SolidBlackState.h"

#include "Systems/FreeCameraControllerSystem.h"

class GalaxyViewerState :
    public SolidBlackState
{
public:
    GalaxyViewerState(Engine& engine);

    void begin();

    void update(double timeStep);

private:
    void _createGalaxy();

    FreeCameraControllerSystem _freeCameraControllerSystem;
};