#include "SolidBlack.h"

ClientLogicLayer::ClientLogicLayer(IpAddress serverAddress, Port port, AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer) :
    _socket(1, 2),
    _assetCache(&assetCache),
    _input(&inputSystem),
    _window(&window),
    _renderingSystem(renderer, assetCache),
    _debugCameraSystem(inputSystem)
{
    _server = _socket.connectToPeer(serverAddress, port);

    _scene.registerComponent<DebugCamera, DebugCameraSerializer>("DebugCamera");

    _scene.addSystem(_cameraSystem);
    _scene.addSystem(_renderingSystem);
    _scene.addSystem(_debugCameraSystem);
    _scene.addSystem(_physicsSystem);

    _input->keyboard().addListener(*this);
    _window->setCursorLocked(true);
}

ClientLogicLayer::~ClientLogicLayer()
{
    _input->keyboard().removeListener(*this);

    if (_server.state() == PeerState::Connected)
    {
        _socket.disconnectFromPeer(_server);

        // Wait for the disconnect event
        SocketEvent event;
        while (_socket.pollEvent(event, TimeSpan::fromSeconds(0.5)))
        {
            if (event.type == SocketEventType::Disconnect)
            {
                break;
            }
        }
    }
}

void ClientLogicLayer::fixedUpdate(double timeStep)
{
    timeStep;

    SocketEvent event;
    while (_socket.pollEvent(event))
    {
        switch (event.type)
        {
        case SocketEventType::Connect:
            LOG_TRACE("Client: Connection established");
            break;
        case SocketEventType::Disconnect:
            LOG_TRACE("Client: Disconnection occurred");
            break;
        case SocketEventType::Receive:
            _receivePacketEvent(event);
            break;
        }
    }

    _cameraSystem.update();
    _debugCameraSystem.update(timeStep);
    _physicsSystem.update(timeStep, 1);
    _scene.refresh();

    _input->updateAxes(timeStep);
}

void ClientLogicLayer::frameUpdate(double delta)
{
    delta;

    if (!_cameraSystem.hasCamera())
    {
        return;
    }

    Camera& camera = _cameraSystem.camera();
    camera.setAspectRatio(_window->aspectRatio());

    _renderingSystem.renderAll(camera, *_window);

    _window->swapBuffers();
}

void ClientLogicLayer::_receivePacketEvent(SocketEvent& event)
{
    PacketReadStream stream = event.packet.readStream();

    uint8_t packetType = stream.readByte();
    switch (packetType)
    {
    case PacketType::AuthorizationRequest:
        _sendAuthorization();
        break;
    case PacketType::CreateEntity:
        {
            Entity::Id id = (Entity::Id)stream.readUnsignedInt();
            LOG_TRACE(format("Client: Creating entity with id '%d'", id));

            std::string entityPath = stream.readString();
            DataValue::Ref entityValue = _assetCache->get<DataValue>(entityPath);

            Entity entity = _scene.createEntity();
            entity.load(*entityValue, *_assetCache);
            entity.activate();
        } break;
    }
}

void ClientLogicLayer::_sendAuthorization()
{
    static const std::string name("Colin");

    LOG_TRACE(format("Client: Sending authorization as '%s'", name.c_str()));

    Packet packet(PacketFlag::Reliable);
    PacketWriteStream stream = packet.writeStream();
    stream.writeByte((uint8_t)PacketType::Authorization);
    stream.writeString(name);

    _socket.sendPacket(_server, 0, packet);
}

void ClientLogicLayer::receiveKeyboardEvent(const KeyboardEvent& event)
{
    if (event.type != KeyboardEventType::KeyDown)
    {
        return;
    }

    if (event.key == Key::Tab)
    {
        bool cursorLocked = _window->isCursorLocked();
        _window->setCursorLocked(!cursorLocked);
    }
    else if (event.key == Key::X)
    {
        _renderingSystem.setExposure(_renderingSystem.exposure() * 2.0);
    }
    else if (event.key == Key::Z)
    {
        _renderingSystem.setExposure(_renderingSystem.exposure() / 2.0);
    }
    else if (event.key == Key::V)
    {
        _renderingSystem.setGamma(_renderingSystem.gamma() + 0.1);
    }
    else if (event.key == Key::C)
    {
        _renderingSystem.setGamma(_renderingSystem.gamma() - 0.1);
    }
}