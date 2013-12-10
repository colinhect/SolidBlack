#include "SolidBlack.h"

TestState::TestState(AssetCache& assetCache, InputSystem& inputSystem, Window& window, Renderer& renderer) :
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

    FileSystem& fileSystem = assetCache.fileSystem();
    if (fileSystem.exists("TestBinary.scene"))
    {
        {
            FileReadStream stream = assetCache.fileSystem().openFileForRead("TestBinary.scene");
            _scene.load(stream, assetCache);
        }
        _scene.refresh();
    }
    else if (fileSystem.exists("Test.scene"))
    {
        DataValue sceneValue;
        {
            FileReadStream stream = assetCache.fileSystem().openFileForRead("Test.scene");
            DataValueJsonFormat::load(sceneValue, stream);
        }
        _scene.load(sceneValue, assetCache);
        _scene.refresh();
    }
    else
    {
        DataValue debugCameraValue;
        {
            FileReadStream stream = assetCache.fileSystem().openFileForRead("Testing/DebugCamera.entity");
            DataValueJsonFormat::load(debugCameraValue, stream);
        }
        _debugCamera = _scene.createEntity();
        _debugCamera.load(debugCameraValue, assetCache);
        _debugCamera.activate();
    }

    DataValue testRigidBodyValue;
    {
        FileReadStream stream = assetCache.fileSystem().openFileForRead("Testing/TestRigidBody.entity");
        DataValueJsonFormat::load(testRigidBodyValue, stream);
    }
    _testRigidBody = _scene.createEntity();
    _testRigidBody.load(testRigidBodyValue, assetCache);
}

TestState::~TestState()
{
    _input->keyboard().removeListener(*this);
}

void TestState::update(double timeStep)
{
    if (!isActivated())
    {
        return;
    }

    _cameraSystem.update();
    _debugCameraSystem.update(timeStep);
    _physicsSystem.update(timeStep, 1);
    _scene.refresh();

    _input->updateAxes(timeStep);
}

void TestState::render(double delta)
{
    delta;

    if (!isActivated() || !_cameraSystem.hasCamera())
    {
        return;
    }

    Camera& camera = _cameraSystem.camera();
    camera.setAspectRatio(_window->aspectRatio());

    _renderingSystem.renderAll(camera, *_window);

    _window->swapBuffers();
}

void TestState::receiveKeyboardEvent(const KeyboardEvent& event)
{
    if (event.type != KeyboardEventType::KeyDown)
    {
        return;
    }

    if (event.key == Key::Esc)
    {
        setDone(true);
    }
    else if (event.key == Key::Tab)
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
            Entity testRigidBody = _testRigidBody.clone();
            Transform& transform = testRigidBody.component<Transform>();
            RigidBody& rigidBody = testRigidBody.component<RigidBody>();

            Camera& camera = _cameraSystem.camera();
            transform.setPosition(camera.position());
            rigidBody.setLinearVelocity(camera.front() * 10);

            testRigidBody.activate();
        }
    }
    else if (event.key == Key::F5)
    {
        DataValue dataValue;
        _scene.save(dataValue);

        FileWriteStream stream = _assetCache->fileSystem().openFileForWrite("Test.scene");
        DataValueJsonFormat::save(dataValue, stream);
    }
    else if (event.key == Key::F6)
    {
        FileWriteStream stream = _assetCache->fileSystem().openFileForWrite("TestBinary.scene");
        _scene.save(stream);
    }
}