#include <Hect.h>

using namespace hect;

#ifdef HECT_WINDOWS
#ifdef HECT_DEBUG
#include <vld.h>
#endif
#endif

#include "States/ServerState.h"

int main()
{
    try
    {
        Engine engine("Solid Black Server", "Settings.json");

        engine.pushState<ServerState>(engine);
        engine.execute();
    }
    catch (std::exception& e)
    {
        Engine::fatalError(e.what());
    }

    return 0;
}