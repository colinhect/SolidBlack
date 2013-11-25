#include <Hect.h>
using namespace hect;

#ifdef HECT_WINDOWS
#ifdef HECT_DEBUG
#include <vld.h>
#endif
#endif

int main()
{
    try
    {
    }
    catch (std::exception& e)
    {
        //Engine::fatalError(e.what());
    }

    return 0;
}