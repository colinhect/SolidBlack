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
        FileSystem fileSystem;
        Path workingDirectory = fileSystem.workingDirectory();
        fileSystem.addDataSource(workingDirectory);

        DataValue settings = JsonParser().parse(fileSystem.openFileForRead("Settings.json"));

        for (const DataValue& dataSource : settings["dataSources"])
        {
            fileSystem.addDataSource(dataSource.asString());
        }

        
        Window window("Solid Black Client", settings);
        Renderer renderer;

        
        // Create the input axes
        InputAxis viewX("ViewX", InputAxisSource::MouseMoveX);
        viewX.setAcceleration(0.0025);
        viewX.setGravity(10);

        InputAxis viewY("ViewY", InputAxisSource::MouseMoveY);
        viewY.setAcceleration(0.0025);
        viewY.setGravity(10);

        InputAxis moveX("MoveX", InputAxisSource::Key);
        moveX.setPositiveKey(Key::D);
        moveX.setNegativeKey(Key::A);
        moveX.setAcceleration(4);
        moveX.setGravity(10);

        InputAxis moveY("MoveY", InputAxisSource::Key);
        moveY.setPositiveKey(Key::W);
        moveY.setNegativeKey(Key::S);
        moveY.setAcceleration(4);
        moveY.setGravity(10);

        InputAxis roll("Roll", InputAxisSource::Key);
        roll.setPositiveKey(Key::E);
        roll.setNegativeKey(Key::Q);
        roll.setAcceleration(4);
        roll.setGravity(10);

        InputAxis adjustSpeed("AdjustSpeed", InputAxisSource::MouseScroll);
        adjustSpeed.setAcceleration(4);
        adjustSpeed.setGravity(1000);

        InputAxis::Array axes;
        axes.push_back(viewX);
        axes.push_back(viewY);
        axes.push_back(moveX);
        axes.push_back(moveY);
        axes.push_back(roll);
        axes.push_back(adjustSpeed);

        InputSystem inputSystem(axes);

        Flow flow;
        flow.push(new TestState(fileSystem, inputSystem, window, renderer, settings));

        while (window.pollEvents(inputSystem) && flow.tick()) { }
    }
    catch (std::exception& e)
    {
        Window::showFatalError(e.what());
    }

    return 0;
}