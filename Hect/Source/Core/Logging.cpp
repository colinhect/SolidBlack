#include "Hect.h"

#ifdef HECT_WINDOWS
#include <Windows.h>
#endif

namespace hect
{

void log(const std::string& category, const std::string& message)
{
    category;

    std::cout << message << std::endl;

#ifdef HECT_DEBUG
#ifdef HECT_WINDOWS
    OutputDebugString((message + "\n").c_str());
#endif
#endif
}

}