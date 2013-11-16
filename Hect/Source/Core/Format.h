#pragma once

namespace hect
{

///
/// Performs printf-style formating on a string with arguments.
///
/// \param fmt The format string.
///
/// \returns The formated string.
std::string format(const char* fmt, ...);

}