#pragma once

#include <Hect.h>
using namespace hect;

#include "RenderingSystem.h"
#include "DebugCameraSystem.h"

class TestState :
    public State,
    public KeyboardListener,
    public Uncopyable
{
public:
    TestState(AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer, const DataValue& settings);
    ~TestState();

    void update(double timeStep);
    void render(double delta);

    void receiveKeyboardEvent(const KeyboardEvent& event);

private:
    AssetCache* _assetCache;
    InputSystem* _input;
    Window* _window;

    CameraSystem _cameraSystem;
    RenderingSystem _renderingSystem;
    DebugCameraSystem _debugCameraSystem;

    Scene _scene;
    EntitySerializer _entitySerializer;
};