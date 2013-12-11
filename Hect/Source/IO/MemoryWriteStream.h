#pragma once

namespace hect
{

///
/// Provides write access to raw data.
class MemoryWriteStream :
    public WriteStream
{
public:

    ///
    /// Constructs the stream given the data to write to.
    ///
    /// \param data The data to write to.
    MemoryWriteStream(std::vector<uint8_t>& data);

    ///
    /// \copydoc WriteStream::writeBytes()
    void writeBytes(const uint8_t* bytes, size_t byteCount);

    ///
    /// \copydoc WriteStream::position()
    size_t position() const;

    ///
    /// \copydoc WriteStream::seek()
    void seek(size_t position);

private:
    std::vector<uint8_t>* _data;
    size_t _position;
};

}