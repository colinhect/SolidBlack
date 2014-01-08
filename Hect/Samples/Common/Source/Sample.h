#pragma once

#include <Hect.h>

using namespace hect;

class Sample
{
public:
    Sample(const std::string& name, const Path& settingsFilePath);

    virtual void initialize() = 0;
    void execute();

protected:
    FileSystem& fileSystem();
    AssetCache& assetCache();
    InputSystem& inputSystem();
    Window& window();
    Renderer& renderer();
    LogicFlow& logicFlow();

private:
    FileSystem _fileSystem;
    AssetCache _assetCache;
    std::unique_ptr<InputSystem> _inputSystem;
    std::unique_ptr<Window> _window;
    std::unique_ptr<Renderer> _renderer;
    LogicFlow _logicFlow;
};