#include "Hect.h"

using namespace hect;

VideoMode VideoModeDataFormat::load(const DataValue& dataValue)
{
    unsigned width = dataValue["width"].asUnsigned();
    unsigned height =  dataValue["height"].asUnsigned();
    unsigned bitsPerPixel = dataValue["bitsPerPixel"].asUnsigned();
    bool fullscreen = dataValue["fullscreen"].asBool();

    return VideoMode(width, height, bitsPerPixel, fullscreen);
}