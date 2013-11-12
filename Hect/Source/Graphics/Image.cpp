#include "Hect.h"

using namespace hect;

Image::Image(unsigned width, unsigned height, PixelType pixelType, PixelFormat pixelFormat, ColorSpace colorSpace) :
    _width(width),
    _height(height),
    _pixelType(pixelType),
    _pixelFormat(pixelFormat),
    _colorSpace(colorSpace)
{
    size_t totalSize = bytesPerPixel() * _width * _height;
    _pixelData = RawPixelData(totalSize, 0);
}

Image::Image(Image&& image) :
    _width(image._width),
    _height(image._height),
    _pixelType(image._pixelType),
    _pixelFormat(image._pixelFormat),
    _colorSpace(image._colorSpace),
    _pixelData(std::move(image._pixelData))
{
}

void Image::flipVertical()
{
    size_t bytesPerRow = bytesPerPixel() * _width;
    RawPixelData newPixelData(_pixelData.size(), 0);
    for (unsigned i = 0; i < _height; ++i)
    {
        size_t sourceRowOffset = bytesPerRow * i;
        size_t destRowOffset = bytesPerRow * (_height - i - 1);
        std::memcpy(&newPixelData[sourceRowOffset], &_pixelData[destRowOffset], bytesPerRow);
    }
    _pixelData = std::move(newPixelData);
}

Image::RawPixelData& Image::pixelData()
{
    return _pixelData;
}

const Image::RawPixelData& Image::pixelData() const
{
    return _pixelData;
}

unsigned Image::width() const
{
    return _width;
}

unsigned Image::height() const
{
    return _height;
}

Image::PixelFormat Image::pixelFormat() const
{
    return _pixelFormat;
}

Image::PixelType Image::pixelType() const
{
    return _pixelType;
}

Image::ColorSpace Image::colorSpace() const
{
    return _colorSpace;
}

int Image::bytesPerPixel() const
{
    int componentCount = 0;

    switch (_pixelFormat)
    {
    case Rgb:
        componentCount = 3;
        break;
    case Rgba:
        componentCount = 4;
        break;
    }

    switch (_pixelType)
    {
    case Float16:
        return componentCount * 2;
        break;
    case Float32:
        return componentCount * 4;
        break;
    case Byte:
        return componentCount * 1;
        break;
    }

    return 0;
}