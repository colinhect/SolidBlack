#include "ClientState.h"

#include "PacketType.h"
#include "Components/FreeCameraController.h"

ClientState::ClientState(Engine& engine) :
    SolidBlackState(engine, 1.0 / 60.0),
    _socket(1, 2),
    _assetCache(engine.storage()),
    _freeCameraControllerSystem(engine.input()),
    _scene(_assetCache)
{
    _server = _socket.connectToPeer(IpAddress::localAddress(), 6006);

    _scene.addSystem(_freeCameraControllerSystem);
}

ClientState::~ClientState()
{
    _scene.removeSystem(_freeCameraControllerSystem);

    if (_server.state() == PeerState::Connected)
    {
        _socket.disconnectFromPeer(_server);

        // Wait for the disconnect event
        SocketEvent event;
        while (_socket.pollEvent(event, TimeSpan::fromSeconds(3)))
        {
            if (event.type == SocketEventType::Disconnect)
            {
                break;
            }
        }
    }
}

void ClientState::begin()
{
    SolidBlackState::begin();

    // Add a free-controlled camera to the scene
    Entity cameraEntity = _scene.createEntity();
    cameraEntity.addComponent<Transform>(Vector3<>(0, 0, 10));
    cameraEntity.addComponent<Camera>(Angle<>::fromDegrees(80), engine().screen().aspectRatio(), 0.01, 250000);
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
    SolidBlackState::end();
}

void ClientState::update(double timeStep)
{
    _scene.update(timeStep);
    _freeCameraControllerSystem.update(timeStep);

    SocketEvent event;
    while (_socket.pollEvent(event))
    {
        switch (event.type)
        {
        case SocketEventType::Connect:
            LOG_INFO("Connection established");
            break;
        case SocketEventType::Disconnect:
            LOG_INFO("Disconnection occurred");
            break;
        case SocketEventType::Receive:
            _receivePacketEvent(event);
            break;
        }
    }
}

void ClientState::render(double delta)
{
    _scene.render(engine().gpu(), engine().screen());
    engine().swapBuffers();
}

void ClientState::receiveKeyboardEvent(const KeyboardEvent& event)
{
    SolidBlackState::receiveKeyboardEvent(event);

    if (event.type != KeyboardEventType::KeyDown)
    {
        return;
    }

    if (event.key == Key::X)
    {
        _scene.setExposure(_scene.exposure() * 2.0);
    }
    else if (event.key == Key::Z)
    {
        _scene.setExposure(_scene.exposure() / 2.0);
    }
    else if (event.key == Key::V)
    {
        _scene.setGamma(_scene.gamma() + 0.1);
    }
    else if (event.key == Key::C)
    {
        _scene.setGamma(_scene.gamma() - 0.1);
    }
}

void ClientState::_receivePacketEvent(SocketEvent& event)
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