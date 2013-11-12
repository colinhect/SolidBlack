#include "Hect.h"

using namespace hect;

#include <lodepng.h>

void ImagePngFormat::load(Image& image, ReadStream& stream)
{
    image._pixelData.clear();

    // Load the PNG pixel data
    size_t length = stream.length();
    Image::RawPixelData encodedPixelData(length, 0);
    stream.readBytes(&encodedPixelData[0], length);

    // Decode the PNG pixel data
    unsigned width = 0;
    unsigned height = 0;
    unsigned error = lodepng::decode(image._pixelData, width, height, encodedPixelData);
    if (error)
    {
        throw Error(format("Failed to decode PNG data: %s", lodepng_error_text(error)));
    }

    image._width = width;
    image._height = height;
    image._pixelType = Image::Byte;
    image._pixelFormat = Image::Rgba;
    image._colorSpace = Image::NonLinear;

    // Flip the image to OpenGL ordering
    image.flipVertical();
}

void ImagePngFormat::save(const Image& image, WriteStream& stream)
{
    // Verify pixel format and type.
    if (image.pixelType() != Image::Byte || image.pixelFormat() != Image::Rgba)
    {
        throw Error("Attempt to save an image to PNG which does not conform to the 32-bit RGBA format");
    }

    // Flip the image from OpenGL ordering
    Image flippedImage = image;
    flippedImage.flipVertical();

    // Encode to PNG data
    Image::RawPixelData encodedPixelData;
    unsigned error = lodepng::encode(encodedPixelData, flippedImage.pixelData(), image.width(), image.height());
    if (error)
    {
        throw Error(format("Failed to encode PNG data: %s", lodepng_error_text(error)));
    }

    // Write the encoded data to disk
    stream.writeBytes(&encodedPixelData[0], encodedPixelData.size());
}