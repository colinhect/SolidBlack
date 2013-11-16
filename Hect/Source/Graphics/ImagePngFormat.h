#pragma once

namespace hect
{

///
/// Provides functionality for loading/saving images from/to PNG data.
class ImagePngFormat
{
public:

    ///
    /// Loads an image from a stream of PNG data.
    ///
    /// \remarks The resulting image will be 32-bit RGBA.
    ///
    /// \param image The image to load to (existing data is lost).
    /// \param stream The stream containing the PNG data.
    void load(Image& image, ReadStream& stream);

    ///
    /// Saves an image as PNG data to a stream.
    ///
    /// \remarks The image must be 32-bit RGBA format.
    ///
    /// \param image The image to save.
    /// \param stream The stream to write the PNG data to.
    void save(const Image& image, WriteStream& stream);
};

}