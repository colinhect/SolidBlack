#pragma once

class TestLogicLayer :
    public LogicLayer,
    public KeyboardListener,
    public Uncopyable
{
public:
    TestLogicLayer(AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer);
    ~TestLogicLayer();

    void fixedUpdate(double timeStep);
    void frameUpdate(double delta);

    void receiveKeyboardEvent(const KeyboardEvent& event);

private:
    AssetCache* _assetCache;
    InputSystem* _input;
    Window* _window;

    CameraSystem _cameraSystem;
    RenderingSystem _renderingSystem;
    DebugCameraSystem _debugCameraSystem;
    PhysicsSystem _physicsSystem;

    Scene _scene;

    Entity _debugCamera;
    Entity _testRigidBody;
};