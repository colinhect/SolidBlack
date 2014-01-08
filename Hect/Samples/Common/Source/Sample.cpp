#include "Sample.h"

Sample::Sample(const std::string& name, const Path& settingsFilePath) :
    _assetCache(_fileSystem),
    _logicFlow(TimeSpan::fromSeconds(1.0 / 60.0))
{
    // Add the working directory as a data source
    Path workingDirectory = _fileSystem.workingDirectory();
    _fileSystem.addDataSource(workingDirectory);

    // Set the working directory as the write directory
    _fileSystem.setWriteDirectory(workingDirectory);

    // Load the settings
    DataValue settings;
    {
        FileReadStream stream = _fileSystem.openFileForRead(settingsFilePath);
        DataValueJsonFormat::load(settings, stream);
    }

    // Add the data sources listed in the settings
    for (const DataValue& dataSource : settings["dataSources"])
    {
        _fileSystem.addDataSource(dataSource.asString());
    }

    // Create window
    VideoMode videoMode = VideoModeDataValueFormat::load(settings["videoMode"]);
    _window.reset(new Window(name, videoMode));
    _renderer.reset(new Renderer(*_window));

    // Load the input axes from the settings
    InputAxis::Array axes;
    for (const std::string& axisName : settings["inputAxes"].memberNames())
    {
        InputAxis axis = InputAxisDataValueFormat::load(axisName, settings["inputAxes"][axisName]);
        axes.push_back(axis);
    }

    // Create input system
    _inputSystem.reset(new InputSystem(axes));
}

void Sample::execute()
{
    initialize();

    while (_window->pollEvents(*_inputSystem))
    {
        if (!_logicFlow.update())
        {
            break;
        }
    }
}

FileSystem& Sample::fileSystem()
{
    return _fileSystem;
}

AssetCache& Sample::assetCache()
{
    return _assetCache;
}

InputSystem& Sample::inputSystem()
{
    return *_inputSystem;
}

Window& Sample::window()
{
    return *_window;
}

Renderer& Sample::renderer()
{
    return *_renderer;
}

LogicFlow& Sample::logicFlow()
{
    return _logicFlow;
}