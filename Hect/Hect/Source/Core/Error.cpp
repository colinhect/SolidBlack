#include "Hect.h"

using namespace hect;

Error::Error() :
    std::runtime_error("")
{
}

Error::Error(const std::string& message) :
    std::runtime_error(message)
{
}