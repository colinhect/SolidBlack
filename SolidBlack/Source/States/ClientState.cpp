#include "ClientState.h"

#include "PacketType.h"
#include "Components/FreeCameraController.h"

ClientState::ClientState(Engine& engine) :
    SolidBlackState(engine, 1.0 / 60.0),
    _socket(1, 2),
    _assetCache(engine.storage()),
    _freeCameraControllerSystem(engine.input()),
    _scene(128)
{
    _server = _socket.connectToPeer(IpAddress::localAddress(), 6006);
}

ClientState::~ClientState()
{
    if (_server.state() == Peer::Connected)
    {
        _socket.disconnectFromPeer(_server);

        // Wait for the disconnect event
        Socket::Event event;
        while (_socket.pollEvent(event, TimeSpan::fromSeconds(3)))
        {
            if (event.type == Socket::Event::Disconnect)
            {
                break;
            }
        }
    }
}

void ClientState::begin()
{
    SolidBlackState::begin();

    _scene.addSystem(_cameraSystem);
    _scene.addSystem(_renderingSystem);
    _scene.addSystem(_debugRenderingSystem);
    _scene.addSystem(_freeCameraControllerSystem);

    Screen& screen = engine().screen();

    // Add a free-controlled camera to the scene
    Entity cameraEntity = _scene.createEntity();
    cameraEntity.addComponent<Transform>(Vector3<>(0, 0, 10));
    cameraEntity.addComponent<Camera>(Angle<>::fromDegrees(80), screen.aspectRatio(), 0.01, 250000);
    cameraEntity.addComponent<FreeCameraController>();
    cameraEntity.activate();
    
    Mesh::Ref mesh = _assetCache.get<Mesh>("Meshes/Test.Cube.mesh");
    Material::Ref material = _assetCache.get<Material>("Materials/Default.material");
      
    Entity meshEntity = _scene.createEntity();
    Transform& transform = meshEntity.addComponent<Transform>(Vector3<>(0, 0, 0));
    Geometry& geometry = meshEntity.addComponent<Geometry>(transform);
    geometry.addMesh(mesh, material);
    meshEntity.activate();

    _scene.refresh();
}

void ClientState::end()
{
    _scene.removeSystem(_freeCameraControllerSystem);
    _scene.removeSystem(_debugRenderingSystem);
    _scene.removeSystem(_renderingSystem);
    _scene.removeSystem(_cameraSystem);

    SolidBlackState::end();
}

void ClientState::update(double timeStep)
{
    _cameraSystem.update();
    _freeCameraControllerSystem.update(timeStep);
    _scene.refresh();

    Socket::Event event;
    while (_socket.pollEvent(event))
    {
        switch (event.type)
        {
        case Socket::Event::Connect:
            LOG_INFO("Connection established");
            break;
        case Socket::Event::Disconnect:
            LOG_INFO("Disconnection occurred");
            break;
        case Socket::Event::Receive:
            _receivePacketEvent(event);
            break;
        }
    }
}

void ClientState::render(double delta)
{
    if (!_cameraSystem.hasCamera())
    {
        return;
    }

    Gpu& gpu = engine().gpu();
    Screen& screen = engine().screen();

    Camera& camera = _cameraSystem.camera();

    gpu.beginFrame();
    gpu.bindTarget(screen);
    gpu.clear();
    _renderingSystem.renderAll(camera, gpu, screen);
    if (debugLevel() == 1)
    {
        _debugRenderingSystem.renderAll(camera, gpu);
    }
    gpu.endFrame();

    engine().swapBuffers();
}

void ClientState::_receivePacketEvent(Socket::Event& event)
{
    PacketReadStream stream = event.packet.readStream();

    uint8_t packetType = stream.readByte();
    switch (packetType)
    {
    case PacketType::AuthorizationRequest:
        _sendAuthorization();
        break;
    }
}

void ClientState::_sendAuthorization()
{
    static const std::string name("Colin");

    LOG_INFO(format("Sending authorization as \"%s\"", name.c_str()));

    Packet packet(PacketFlag::Reliable);
    PacketWriteStream stream = packet.writeStream();
    stream.writeByte(PacketType::Authorization);
    stream.writeString(name);

    _socket.sendPacket(_server, 0, packet);
    _socket.flush();
}