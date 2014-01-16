#include <Hect.h>
using namespace hect;

#ifdef HECT_WINDOWS
#ifdef HECT_DEBUG
#include <vld.h>
#endif
#endif

void runSample(FileSystem& fileSystem, Window& window, Renderer& renderer, const DataValue& settings);

int main(int argc, const char* argv[])
{
    argc;
    argv;

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
        Window window("Sample", videoMode);
        Renderer renderer(window);

        // Run the sample
        runSample(fileSystem, window, renderer, settings);
    }
    catch (Error& error)
    {
        Window::showFatalError(error.what());
    }

    return 0;
}