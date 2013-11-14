namespace hect
{

///
/// A 2-dimensional image.
class Image
{
    friend class ImagePngFormat;
public:

    ///
    /// A shared reference to an image.
    typedef std::shared_ptr<Image> Ref;

    ///
    /// Raw pixel data.
    typedef std::vector<uint8_t> RawPixelData;

    ///
    /// The type of each component in a pixel.
    enum PixelType
    {
        ///
        /// 16-bit floating point.
        Half,

        ///
        /// 32-bit floating point.
        Float,

        ///
        /// A byte.
        Byte
    };

    ///
    /// The layout of the component(s) in a pixel.
    enum PixelFormat
    {
        ///
        /// Red, green, and blue channels.
        Rgb,

        ///
        /// Red, green, blue, and alpha channels.
        Rgba
    };

    ///
    /// The color space a pixel is in.
    enum ColorSpace
    {
        ///
        /// Non-linear color space (sRGB).
        ///
        /// \remarks Only an image with a pixel type of PixelType::Byte can
        /// be non-linear.
        NonLinear,

        ///
        /// Linear color space.
        Linear
    };

    ///
    /// Constructs a solid black image.
    ///
    /// \param width The width.
    /// \param height The height.
    /// \param pixelType The pixel type.
    /// \param pixelFormat The pixel format.
    /// \param colorSpace The color space.
    Image(unsigned width = 1, unsigned height = 1, PixelType pixelType = Byte, PixelFormat pixelFormat = Rgba, ColorSpace colorSpace = Linear);

    ///
    /// Constructs an image moved from another.
    ///
    /// \param image The image to move.
    Image(Image&& image);

    ///
    /// Flips the image vertically.
    void flipVertical();

    ///
    /// Returns the raw pixel data.
    RawPixelData& pixelData();

    ///
    /// Returns the raw pixel data.
    const RawPixelData& pixelData() const;

    ///
    /// Returns the width.
    unsigned width() const;

    ///
    /// Returns the height.
    unsigned height() const;

    ///
    /// Returns the pixel type.
    PixelType pixelType() const;

    ///
    /// Returns the pixel format.
    PixelFormat pixelFormat() const;

    ///
    /// Returns the color space.
    ColorSpace colorSpace() const;

    ///
    /// Returns the number of bytes in a pixel of this image.
    int bytesPerPixel() const;

private:
    unsigned _width;
    unsigned _height;

    PixelType _pixelType;
    PixelFormat _pixelFormat;

    ColorSpace _colorSpace;

    RawPixelData _pixelData;
};

}