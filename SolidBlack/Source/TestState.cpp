#include "TestState.h"

#include "PacketType.h"
#include "FreeCameraController.h"

TestState::TestState(Engine& engine) :
    State(engine, 1.0 / 60.0),
    _assetCache(engine.storage()),
    _renderingSystem(_assetCache, engine.settings()),
    _freeCameraControllerSystem(engine.input()),
    _scene(128)
{
}

void TestState::begin()
{
    _scene.addSystem(_cameraSystem);
    _scene.addSystem(_renderingSystem);
    _scene.addSystem(_freeCameraControllerSystem);

    Keyboard& keyboard = engine().input().keyboard();
    keyboard.addListener(*this);

    Mouse& mouse = engine().input().mouse();
    mouse.setCursorLocked(true);

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

void TestState::end()
{
    Keyboard& keyboard = engine().input().keyboard();
    keyboard.removeListener(*this);

    _scene.addSystem(_freeCameraControllerSystem);
    _scene.addSystem(_renderingSystem);
    _scene.addSystem(_cameraSystem);
}

void TestState::update(double timeStep)
{
    _cameraSystem.update();
    _freeCameraControllerSystem.update(timeStep);
    _scene.refresh();
}

void TestState::render(double delta)
{
    if (!_cameraSystem.hasCamera())
    {
        return;
    }

    Camera& camera = _cameraSystem.camera();
    _renderingSystem.renderAll(camera, engine().gpu(), engine().screen());

    engine().swapBuffers();
}

void TestState::receiveKeyboardEvent(const KeyboardEvent& event)
{
    if (event.type != KeyboardEventType::KeyDown)
    {
        return;
    }

    if (event.key == Key::Esc)
    {
        setActive(false);
    }
    else if (event.key == Key::Tab)
    {
        Mouse& mouse = engine().input().mouse();
        mouse.setCursorLocked(!mouse.isCursorLocked());
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