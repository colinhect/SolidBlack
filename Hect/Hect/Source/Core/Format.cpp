#include "Hect.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

namespace hect
{

std::string format(const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    char buffer[4096];
    vsprintf(buffer, fmt, args);

    va_end(args);

    return std::string(buffer);
}

}