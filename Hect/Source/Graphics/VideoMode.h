#pragma once

namespace hect
{

///
/// Describes the video mode a window uses.
class VideoMode
{
public:

    ///
    /// Constructs a default video mode.
    VideoMode();

    ///
    /// Constructs a video mode.
    ///
    /// \param width The width.
    /// \param height The height.
    /// \param bitsPerPixel The bits per pixel.
    /// \param fullscreen True if a fullscreen mode should be used.
    VideoMode(unsigned width, unsigned height, unsigned bitsPerPixel, bool fullscreen);

    ///
    /// Returns the width.
    unsigned width() const;

    ///
    /// Returns the height.
    unsigned height() const;

    ///
    /// Returns the bits per pixel.
    unsigned bitsPerPixel() const;
    
    ///
    /// Returns whether fullscreen is enabled.
    bool isFullscreen() const;

private:
    unsigned _width;
    unsigned _height;
    unsigned _bitsPerPixel;
    bool _fullscreen;
};

}