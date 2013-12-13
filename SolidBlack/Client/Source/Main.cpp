#include <Hect.h>
using namespace hect;

#ifdef HECT_WINDOWS
#ifdef HECT_DEBUG
#include <vld.h>
#endif
#endif

#include "SolidBlack.h"

int main()
{
    try
    {
        // Create file system
        FileSystem fileSystem;

        // Add the working directory as a data source
        Path workingDirectory = fileSystem.workingDirectory();
        fileSystem.addDataSource(workingDirectory);

        // Set the working directory as the write directory
        fileSystem.setWriteDirectory(workingDirectory);

        // Load the settings
        DataValue settings;
        {
            FileReadStream stream = fileSystem.openFileForRead("Settings.json");
            DataValueJsonFormat::load(settings, stream);
        }

        // Add the data sources listed in the settings
        for (const DataValue& dataSource : settings["dataSources"])
        {
            fileSystem.addDataSource(dataSource.asString());
        }

        // Create window
        VideoMode videoMode = VideoModeDataValueFormat::load(settings["videoMode"]);
        Window window("Solid Black Client", videoMode);
        Renderer renderer(window);

        // Load the input axes from the settings
        InputAxis::Array axes;
        for (const std::string& axisName : settings["inputAxes"].memberNames())
        {
            InputAxis axis = InputAxisDataValueFormat::load(axisName, settings["inputAxes"][axisName]);
            axes.push_back(axis);
        }

        // Create input system
        InputSystem inputSystem(axes);

        // Create asset cache
        AssetCache assetCache(fileSystem);

        // Server logic flow
        LogicFlow serverLogicFlow;
        ServerLogicLayer serverLogicLayer(assetCache);
        serverLogicFlow.addLayer(serverLogicLayer);

        // Client logic flow
        LogicFlow clientLogicFlow;
        BaseLogicLayer baseLogicLayer(clientLogicFlow, inputSystem);
        clientLogicFlow.addLayer(baseLogicLayer);
        ClientLogicLayer clientLogicLayer(IpAddress::localAddress(), 6006);
        clientLogicFlow.addLayer(clientLogicLayer);
        //TestLogicLayer testLogicLayer(assetCache, inputSystem, window, renderer);
        //clientLogicFlow.addLayer(testLogicLayer);
        
        TimeSpan clientTimeStep = TimeSpan::fromSeconds(1.0 / 60.0);
        TimeSpan serverTimeStep = TimeSpan::fromSeconds(1.0 / 30.0);

        while (window.pollEvents(inputSystem))
        {
            if (!clientLogicFlow.update(clientTimeStep) || !serverLogicFlow.update(serverTimeStep))
            {
                break;
            }
        }
    }
    catch (Error& error)
    {
        Window::showFatalError(error.what());
    }

    return 0;
}