#include "ServerState.h"

#include "PacketType.h"
#include "Components/FreeCameraController.h"

ServerState::ServerState(Engine& engine) :
    SolidBlackState(engine, 1.0 / 30.0),
    _assetCache(engine.storage()),
    _socket(Port, MaxPlayerCount, ChannelCount)
{
    _bubbles.push_back(Bubble::Ref(new Bubble()));
}

void ServerState::begin()
{
    SolidBlackState::begin();
}

void ServerState::end()
{
    SolidBlackState::end();
}

void ServerState::update(double timeStep)
{
    Socket::Event event;
    while (_socket.pollEvent(event))
    {
        switch (event.type)
        {
        case Socket::Event::Connect:
            _connectionEvent(event);
            break;
        case Socket::Event::Disconnect:
            _disconnectionEvent(event);
            break;
        case Socket::Event::Receive:
            _receivePacketEvent(event);
            break;
        }
    }

    for (const Bubble::Ref& bubble : _bubbles)
    {
        bubble->update(timeStep);
    }
}

void ServerState::render(double delta)
{
    engine().swapBuffers();
}

void ServerState::notifyKeyboardEvent(const Keyboard::Event& event)
{
    if (event.type != Keyboard::Event::KeyDown)
    {
        return;
    }

    if (event.key == Keyboard::Esc)
    {
        setActive(false);
    }
}

void ServerState::_connectionEvent(Socket::Event& event)
{
    Peer::Id peerId = event.peer.id();
    LOG_INFO(format("Connection (peerId  = %d)", peerId));

    Player& player = _players[peerId];
    if (player.authorized)
    {
        LOG_INFO("Player is already authorized");
    }
    else
    {
        _sendAuthorizationRequest(event.peer);
    }
}

void ServerState::_disconnectionEvent(Socket::Event& event)
{
    Peer::Id peerId = event.peer.id();
    Player& player = _players[peerId];
    if (player.authorized)
    {
        LOG_INFO(format("Player \"%s\" disconnected (peerId  = %d)", player.name.c_str(), peerId));
        player.authorized = false;
        player.name = "";
    }
    else
    {
        LOG_INFO(format("Unauthorized player disconnected (peerId  = %d)", peerId));
    }
}

void ServerState::_receivePacketEvent(Socket::Event& event)
{
    Peer::Id peerId = event.peer.id();
    Player& player = _players[peerId];

    PacketReadStream stream = event.packet.readStream();
    uint8_t packetType = stream.readByte();

    switch (packetType)
    {
    case PacketType::Authorization: {
            std::string name = stream.readString();
            player.authorized = true;
            player.name = name;

            LOG_INFO(format("Player authorized as \"%s\" (peerId  = %d)", name.c_str(), peerId));
        } break;
    }
}

void ServerState::_sendAuthorizationRequest(Peer peer)
{
    LOG_INFO("Requesting player authorization");

    Packet packet(PacketFlag::Reliable);
    PacketWriteStream stream = packet.writeStream();
    stream.writeByte(PacketType::AuthorizationRequest);
    _socket.sendPacket(peer, 0, packet);
    _socket.flush();
}
/*
#include "ServerState.h"

#include "Common/Components/FreeCameraController.h"

ServerState::ServerState(Engine& engine) :
    SolidBlackState(engine, 1.0 / 60.0),
    _assetCache(engine.storage()),
    _socket(Port, MaxPlayerCount, ChannelCount),
    _freeCameraControllerSystem(engine.input()),
    _scene(128)
{
    _scene.addSystem(_cameraSystem);
    _scene.addSystem(_renderingSystem);
    _scene.addSystem(_debugRenderingSystem);
    _scene.addSystem(_freeCameraControllerSystem);
}

void ServerState::begin()
{
    SolidBlackState::begin();

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

void ServerState::end()
{
    SolidBlackState::end();
}

void ServerState::update(double timeStep)
{
    _cameraSystem.update();
    _freeCameraControllerSystem.update(timeStep);
    _scene.refresh();

    Socket::Event event;
    while (_socket.pollEvent(event))
    {
        Peer peer = event.peer;
        std::string address = peer.address().toString();

        switch (event.type)
        {
        case Socket::Event::Connect:
            LOG_INFO(format("[%d] Connect (%s)", peer.id(), address.c_str()));
            break;
        case Socket::Event::Disconnect:
            LOG_INFO(format("[%d] Disconnect (%s)", peer.id(), address.c_str()));
            break;
        }
    }
}

void ServerState::render(double delta)
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

void ServerState::notifyKeyboardEvent(const Keyboard::Event& event)
{
    if (event.type != Keyboard::Event::KeyDown)
    {
        return;
    }

    if (event.key == Keyboard::Esc)
    {
        setActive(false);
    }
}
*/