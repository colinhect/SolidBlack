#include "ServerState.h"

#include "Common/Components/FreeCameraController.h"

ServerState::ServerState(Engine& engine) :
    SolidBlackState(engine, 1.0 / 60.0),
    _assetCache(engine.storage()),
    _socket(6006, 256, 2),
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