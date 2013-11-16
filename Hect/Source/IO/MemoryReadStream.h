#pragma once

namespace hect
{

///
/// Provides read access to raw data.
class MemoryReadStream :
    public ReadStream
{
public:

    ///
    /// Constructs the stream given the data to read from.
    ///
    /// \param data The data to read from.
    MemoryReadStream(const std::vector<uint8_t>& data);

    ///
    /// \copydoc ReadStream::readBytes()
    void readBytes(uint8_t* bytes, size_t byteCount);

    ///
    /// \copydoc ReadStream::endOfStream()
    bool endOfStream() const;

    ///
    /// \copydoc ReadStream::length()
    size_t length() const;

    ///
    /// \copydoc ReadStream::position()
    size_t position() const;

    ///
    /// \copydoc ReadStream::seek()
    void seek(size_t position);

private:
    const std::vector<uint8_t>* _data;
    size_t _position;
};

}