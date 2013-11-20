#pragma once

namespace hect
{

///
/// Describes how a texture pixel is rendered when magnified or minified.
enum class TextureFilter
{
    ///
    /// The nearest pixel is selected.
    Nearest,

    /// The pixel is interpolated linearly.
    Linear
};

///
/// A 2-dimensional texture.
class Texture :
    public GpuObject
{
    friend class Gpu;
public:

    ///
    /// A shared reference to a texture.
    typedef std::shared_ptr<Texture> Ref;

    ///
    /// An array of textures.
    typedef std::vector<Texture> Array;

    ///
    /// An array of shared texture references.
    typedef std::vector<Texture::Ref> RefArray;

    ///
    /// Constructs a default 2-dimensional texture.
    Texture();

    ///
    /// Constructs a 2-dimensional texture given its properties.
    ///
    /// \param width The width.
    /// \param height The height.
    /// \param pixelType The pixel type.
    /// \param pixelFormat The pixel format.
    /// \param minFilter The minification filter.
    /// \param magFilter The Magnification filter.
    /// \param mipmapped True if the texture is mipmapped; false otherwise.
    /// \param wrapped True if the texture is wrapped; false otherwise.
    Texture(unsigned width, unsigned height, PixelType pixelType, PixelFormat pixelFormat, TextureFilter minFilter, TextureFilter magFilter, bool mipmapped, bool wrapped);

    ///
    /// Constructs a 2-dimensional texture given a source image.
    ///
    /// \remarks Once the texture is uploaded it will no longer hold a
    /// reference to the source image.
    ///
    /// \param image The source image.
    Texture(Image::Ref image);

    ///
    /// Constructs a copy of another texture.
    ///
    /// \param texture The texture to copy.
    Texture(const Texture& texture);

    ///
    /// Destroys the texture on the GPU if it is uploaded.
    ~Texture();

    ///
    /// Returns the minification filter.
    TextureFilter minFilter() const;

    ///
    /// Sets the minification filter.
    ///
    /// \param filter The new minification filter.
    ///
    /// \throws Error If the texture is uploaded.
    void setMinFilter(TextureFilter filter);

    ///
    /// Returns the magnification filter.
    TextureFilter magFilter() const;

    ///
    /// Sets the magnification filter.
    ///
    /// \param filter The new magnification filter.
    ///
    /// \throws Error If the texture is uploaded.
    void setMagFilter(TextureFilter filter);

    ///
    /// Returns whether the texture is mipmapped.
    bool isMipmapped() const;

    ///
    /// Sets whether the texture is mipmapped.
    ///
    /// \param mipmapped True if the texture is mipmapped; false otherwise.
    ///
    /// \throws Error If the texture is uploaded.
    void setMipmapped(bool mipmapped);

    ///
    /// Returns whether the texture is wrapped.
    bool isWrapped() const;

    ///
    /// Sets whether the texture is wrapped.
    ///
    /// \param wrapped True if the texture is wrapped; false otherwise.
    ///
    /// \throws Error If the texture is uploaded.
    void setWrapped(bool wrapped);

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
    /// Returns the number of bytes in a pixel of this texture.
    int bytesPerPixel() const;

private:

    // A texture will only have an image if it hasn't been uploaded yet
    Image::Ref _image;

    unsigned _width;
    unsigned _height;

    PixelType _pixelType;
    PixelFormat _pixelFormat;

    TextureFilter _minFilter;
    TextureFilter _magFilter;

    bool _mipmapped;
    bool _wrapped;
};

}