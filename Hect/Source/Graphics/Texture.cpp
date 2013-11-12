#include "Hect.h"

using namespace hect;

Texture::Texture() :
    _image(Image::Ref(new Image())),
    _width(_image->width()),
    _height(_image->height()),
    _pixelType(_image->pixelType()),
    _pixelFormat(_image->pixelFormat()),
    _minFilter(Filter::Linear),
    _magFilter(Filter::Linear),
    _mipmapped(true),
    _wrapped(false)
{
}

Texture::Texture(unsigned width, unsigned height, Image::PixelType pixelType, Image::PixelFormat pixelFormat, Texture::Filter minFilter, Texture::Filter magFilter, bool mipmapped, bool wrapped) :
    _image(Image::Ref(new Image(width, height, pixelType, pixelFormat))),
    _width(width),
    _height(height),
    _pixelType(pixelType),
    _pixelFormat(pixelFormat),
    _minFilter(minFilter),
    _magFilter(magFilter),
    _mipmapped(mipmapped),
    _wrapped(wrapped)
{
}

Texture::Texture(Image::Ref image) :
    _image(image),
    _width(_image->width()),
    _height(_image->height()),
    _pixelType(_image->pixelType()),
    _pixelFormat(_image->pixelFormat()),
    _minFilter(Filter::Linear),
    _magFilter(Filter::Linear),
    _mipmapped(true),
    _wrapped(false)
{
}

Texture::Texture(const Texture& texture) :
    _image(texture._image),
    _width(texture.width()),
    _height(texture.height()),
    _pixelType(texture.pixelType()),
    _pixelFormat(texture.pixelFormat()),
    _minFilter(texture.minFilter()),
    _magFilter(texture.magFilter()),
    _mipmapped(texture.isMipmapped()),
    _wrapped(texture.isWrapped())
{
    if (texture.isUploaded())
    {
        // Download the image for the source texture and copy to the heap as
        // the source image for this texture
        _image = Image::Ref(new Image(texture.gpu()->downloadTextureImage(texture)));
    }
}

Texture::~Texture()
{
    if (isUploaded())
    {
        gpu()->destroyTexture(*this);
    }
}

Texture::Filter Texture::minFilter() const
{
    return _minFilter;
}

void Texture::setMinFilter(Filter filter)
{
    if (isUploaded())
    {
        throw Error("Attempt to set the min filter of a texture that is uploaded");
    }

    _minFilter = filter;
}

Texture::Filter Texture::magFilter() const
{
    return _magFilter;
}

void Texture::setMagFilter(Filter filter)
{
    if (isUploaded())
    {
        throw Error("Attempt to set the mag filter of a texture that is uploaded");
    }

    _magFilter = filter;
}

bool Texture::isMipmapped() const
{
    return _mipmapped;
}

void Texture::setMipmapped(bool mipmapped)
{
    if (isUploaded())
    {
        throw Error("Attempt to set mipmapping of a texture that is uploaded");
    }

    _mipmapped = mipmapped;
}

bool Texture::isWrapped() const
{
    return _wrapped;
}

void Texture::setWrapped(bool wrapped)
{
    if (isUploaded())
    {
        throw Error("Attempt to set wrapping of a texture that is uploaded");
    }

    _wrapped = wrapped;
}

unsigned Texture::width() const
{
    return _width;
}

unsigned Texture::height() const
{
    return _height;
}

Image::PixelFormat Texture::pixelFormat() const
{
    return _pixelFormat;
}

Image::PixelType Texture::pixelType() const
{
    return _pixelType;
}

int Texture::bytesPerPixel() const
{
    int componentCount = 0;

    switch (_pixelFormat)
    {
    case Image::Rgb:
        componentCount = 3;
        break;
    case Image::Rgba:
        componentCount = 4;
        break;
    }

    switch (_pixelType)
    {
    case Image::Float16:
        return componentCount * 2;
        break;
    case Image::Float32:
        return componentCount * 4;
        break;
    case Image::Byte:
        return componentCount * 1;
        break;
    }

    return 0;
}