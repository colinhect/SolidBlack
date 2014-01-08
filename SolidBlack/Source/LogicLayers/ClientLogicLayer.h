#pragma once

class ClientLogicLayer :
    public LogicLayer,
    public Listener<KeyboardEvent>,
    public Uncopyable
{
public:
    ClientLogicLayer(IpAddress serverAddress, Port port, AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer);
    ~ClientLogicLayer();
    
    void fixedUpdate(double timeStep);
    void frameUpdate(double delta);

    void receiveEvent(const KeyboardEvent& event);

private:
    void _receivePacketEvent(SocketEvent& event);
    void _sendAuthorization();

    Socket _socket;
    Peer _server;

    AssetCache* _assetCache;
    InputSystem* _input;
    Window* _window;

    CameraSystem _cameraSystem;
    RenderingSystem _renderingSystem;
    DebugCameraSystem _debugCameraSystem;
    PhysicsSystem _physicsSystem;

    Scene _scene;
};