#pragma once

#include <Hect.h>
using namespace hect;

#include "DeferredRenderingSystem.h"

class TestState :
    public State,
    public KeyboardListener,
    public Uncopyable
{
public:
    TestState(Engine& engine);

    void begin(Flow& flow);
    void end(Flow& flow);

    void update(double timeStep);
    void render(double delta);

    void receiveKeyboardEvent(const KeyboardEvent& event);

private:
    Engine* _engine;

    AssetCache _assetCache;

    CameraSystem _cameraSystem;
    DeferredRenderingSystem _renderingSystem;
    BehaviorSystem _behaviorSystem;

    Scene _scene;
};