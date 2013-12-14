#include "SolidBlack.h"

TestLogicLayer::TestLogicLayer(AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer) :
    _assetCache(&assetCache),
    _input(&inputSystem),
    _window(&window),
    _renderingSystem(renderer, assetCache),
    _debugCameraSystem(inputSystem)
{
    _scene.registerComponent<DebugCamera, DebugCameraSerializer>("DebugCamera");

    _scene.addSystem(_cameraSystem);
    _scene.addSystem(_renderingSystem);
    _scene.addSystem(_debugCameraSystem);
    _scene.addSystem(_physicsSystem);

    _input->keyboard().addListener(*this);
    _window->setCursorLocked(true);

    DataValue::Ref debugCameraValue = assetCache.get<DataValue>("Testing/DebugCamera.entity");
    _debugCamera = _scene.createEntity();
    _debugCamera.load(*debugCameraValue, assetCache);
    _debugCamera.activate();

    DataValue::Ref sunValue = assetCache.get<DataValue>("Sun.Client.entity");
    Entity sun = _scene.createEntity();
    sun.load(*sunValue, assetCache);
    sun.activate();

    DataValue::Ref testRigidBodyValue = assetCache.get<DataValue>("Testing/TestRigidBody.entity");
    _testRigidBody = _scene.createEntity();
    _testRigidBody.load(*testRigidBodyValue, assetCache);
}

TestLogicLayer::~TestLogicLayer()
{
    _input->keyboard().removeListener(*this);
}

void TestLogicLayer::fixedUpdate(double timeStep)
{
    _cameraSystem.update();
    _debugCameraSystem.update(timeStep);
    _physicsSystem.update(timeStep, 1);
    _scene.refresh();

    _input->updateAxes(timeStep);
}

void TestLogicLayer::frameUpdate(double delta)
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

void TestLogicLayer::receiveKeyboardEvent(const KeyboardEvent& event)
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
    else if (event.key == Key::F)
    {
        if (_cameraSystem.hasCamera())
        {
            Camera& camera = _cameraSystem.camera();

            Entity testRigidBody = _testRigidBody.clone();

            Transform& transform = testRigidBody.component<Transform>();
            transform.setPosition(camera.position());

            RigidBody& rigidBody = testRigidBody.component<RigidBody>();
            rigidBody.setLinearVelocity(camera.front() * 10);

            testRigidBody.activate();
        }
    }
    /*
    else if (event.key == Key::F5)
    {
        DataValue dataValue;
        _scene.save(dataValue);
        
        FileSystem& fileSystem = _assetCache->fileSystem();
        FileWriteStream stream = fileSystem.openFileForWrite("Test.scene");
        DataValueJsonFormat::save(dataValue, stream);
    }
    else if (event.key == Key::F6)
    {
        FileSystem& fileSystem = _assetCache->fileSystem();
        FileWriteStream stream = fileSystem.openFileForWrite("TestBinary.scene");
        _scene.save(stream);
    }
    */
}