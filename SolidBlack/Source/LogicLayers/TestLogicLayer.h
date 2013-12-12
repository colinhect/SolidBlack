#pragma once

class TestLogicLayer :
    public LogicLayer,
    public KeyboardListener,
    public Uncopyable
{
public:
    TestLogicLayer(Logic& logic, AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer);
    ~TestLogicLayer();

    void update(double timeStep);
    void render(double delta);

    void receiveKeyboardEvent(const KeyboardEvent& event);

private:
    Logic* _logic;
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