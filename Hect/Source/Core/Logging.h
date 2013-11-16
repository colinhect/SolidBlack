#pragma once

namespace hect
{

// \cond INTERNAL

void log(const std::string& category, const std::string& message);

// \endcond

#ifdef HECT_DEBUG
#ifndef HECT_NO_LOGGING
#define LOG_TRACE(message) log("Trace", message)
#define LOG_DEBUG(message) log("Debug", message)
#else
#define LOG_TRACE(message)
#define LOG_DEBUG(message)
#endif
#else
#define LOG_TRACE(message)
#define LOG_DEBUG(message)
#endif

#ifndef HECT_NO_LOGGING
#define LOG_INFO(message) log("Info", message)
#define LOG_WARNING(message) log("Warning", message)
#define LOG_ERROR(message) log("Error", message)
#else
#define LOG_INFO(message)
#define LOG_WARNING(message)
#define LOG_ERROR(message)
#endif

}