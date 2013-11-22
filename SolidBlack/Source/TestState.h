#pragma once

#include <Hect.h>
using namespace hect;

#include "FreeCameraControllerSystem.h"
#include "DeferredRenderingSystem.h"

class TestState :
    public State,
    public KeyboardListener,
    public Uncopyable
{
public:
    TestState(Engine& engine);

    void begin();
    void end();

    void update(double timeStep);
    void render(double delta);

    void receiveKeyboardEvent(const KeyboardEvent& event);

private:
    AssetCache _assetCache;

    CameraSystem _cameraSystem;
    DeferredRenderingSystem _renderingSystem;
    FreeCameraControllerSystem _freeCameraControllerSystem;

    Scene _scene;
    EntityFactory _factory;
};