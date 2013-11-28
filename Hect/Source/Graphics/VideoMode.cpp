#include "Hect.h"

using namespace hect;

VideoMode::VideoMode() :
    _width(800),
    _height(600),
    _bitsPerPixel(32),
    _fullscreen(false)
{
}

VideoMode::VideoMode(unsigned width, unsigned height, unsigned bitsPerPixel, bool fullscreen) :
    _width(width),
    _height(height),
    _bitsPerPixel(bitsPerPixel),
    _fullscreen(fullscreen)
{
}

unsigned VideoMode::width() const
{
    return _width;
}

unsigned VideoMode::height() const
{
    return _height;
}

unsigned VideoMode::bitsPerPixel() const
{
    return _bitsPerPixel;
}

bool VideoMode::isFullscreen() const
{
    return _fullscreen;
}