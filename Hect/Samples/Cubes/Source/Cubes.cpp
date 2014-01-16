#include "MainLogicLayer.h"

void runSample(FileSystem& fileSystem, Window& window, Renderer& renderer, const DataValue& settings)
{
    // Create the asset cache
    AssetCache assetCache(fileSystem);

    // Load the input axes from the settings
    InputAxis::Array axes;
    for (const std::string& axisName : settings["inputAxes"].memberNames())
    {
        InputAxis axis = InputAxisDataValueFormat::load(axisName, settings["inputAxes"][axisName]);
        axes.push_back(axis);
    }

    // Create the input system
    InputSystem inputSystem(axes);

    // Create the logic flow
    MainLogicLayer main(assetCache, inputSystem, window, renderer);
    LogicFlow logicFlow(TimeSpan::fromSeconds(1.0 / 60.0));
    logicFlow.addLayer(main);

    // Update until the flow is complete
    while (window.pollEvents(inputSystem))
    {
        if (!logicFlow.update())
        {
            break;
        }
    }
}