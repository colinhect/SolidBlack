#include "CubesSample.h"

CubesSample::CubesSample() :
    Sample("Cubes")
{
}

void CubesSample::execute()
{
    InputSystem inputSystem;
    LogicFlow logicFlow(TimeSpan::fromSeconds(1.0 / 60.0));

    while (window().pollEvents(inputSystem))
    {
        if (!logicFlow.update())
        {
            break;
        }
    }    
}