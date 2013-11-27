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
            InputAxis axis = InputAxisDataFormat().load(axisName, settings["inputAxes"][axisName]);
            axes.push_back(axis);
        }
        
        // Create input system
        InputSystem inputSystem(axes);

        // Create asset cache
        AssetCache assetCache(fileSystem);

        // Create flow
        Flow flow;
        flow.push(new TestState(assetCache, inputSystem, window, renderer, settings));

        // Execute flow until the window closes or the flow has no more states
        while (window.pollEvents(inputSystem))
        {
            if (!flow.tick())
            {
                break;
            }
        }
    }
    catch (std::exception& e)
    {
        Window::showFatalError(e.what());
    }

    return 0;
}