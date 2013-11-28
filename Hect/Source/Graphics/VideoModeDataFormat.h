#pragma once

namespace hect
{

///
/// Provides functionality for loading video modes from data values.
class VideoModeDataFormat
{
public:

    ///
    /// Loads a video mode from a data value.
    ///
    /// \param dataValue The data value to load the video mode from.
    ///
    /// \returns The video mode.
    ///
    /// \throws Error If an error occurred while loading the video mode.
    static VideoMode load(const DataValue& dataValue);
};

}