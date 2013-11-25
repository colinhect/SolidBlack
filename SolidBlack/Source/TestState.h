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
    TestState(Storage& storage, Input& input, Window& window, Gpu& gpu, const DataValue& settings);

    void begin(Flow& flow);
    void end(Flow& flow);

    void update(double timeStep);
    void render(double delta);

    void receiveKeyboardEvent(const KeyboardEvent& event);

private:
    Storage* _storage;
    Input* _input;
    Window* _window;
    Gpu* _gpu;

    AssetCache _assetCache;

    CameraSystem _cameraSystem;
    DeferredRenderingSystem _renderingSystem;
    BehaviorSystem _behaviorSystem;

    Scene _scene;
};