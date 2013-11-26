#pragma once

namespace hect
{

///
/// Provides read access to a file.
class FileReadStream :
    public ReadStream,
    public Uncopyable
{
    friend class FileSystem;
public:

    ///
    /// Closes the file stream.
    ~FileReadStream();

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
    FileReadStream(const Path& path);

    Path _path;
    void* _handle;
};

}