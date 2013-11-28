#include <Hect.h>
using namespace hect;

#ifdef HECT_WINDOWS
#ifdef HECT_DEBUG
#include <vld.h>
#endif
#endif

#include "TestState.h"

int main()
{
    try
    {
        // Create file system
        FileSystem fileSystem;

        // Add the working directory as a data source
        Path workingDirectory = fileSystem.workingDirectory();
        fileSystem.addDataSource(workingDirectory);

        // Load the settings
        DataValue settings = DataJsonFormat::load(fileSystem.openFileForRead("Settings.json"));
        
        // Add the data sources listed in the settings
        for (const DataValue& dataSource : settings["dataSources"])
        {
            fileSystem.addDataSource(dataSource.asString());
        }

        // Create window/renderer
        Window window("Solid Black Client", settings);
        Renderer renderer(window);

        // Load the input axes from the settings
        InputAxis::Array axes;
        for (const std::string& axisName : settings["inputAxes"].memberNames())
        {
            InputAxis axis = InputAxisDataFormat::load(axisName, settings["inputAxes"][axisName]);
            axes.push_back(axis);
        }
        
        // Create input system
        InputSystem inputSystem(axes);

        // Create asset cache
        AssetCache assetCache(fileSystem);

        StateFlow stateFlow;
        
        State::Ref testState(new TestState(assetCache, inputSystem, window, renderer, settings));
        stateFlow.push(testState);

        TimeSpan timeStep = TimeSpan::fromSeconds(1.0 / 60.0);

        while (window.pollEvents(inputSystem) && stateFlow.transition())
        {
            stateFlow.update(timeStep);
        }
    }
    catch (Error& error)
    {
        Window::showFatalError(error.what());
    }

    return 0;
}