#pragma once

namespace hect
{

///
/// Provides write access to a file.
class FileWriteStream :
    public WriteStream,
    public Uncopyable
{
    friend class FileSystem;
public:

    ///
    /// Closes the file stream.
    ~FileWriteStream();

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
    FileWriteStream(const Path& path);

    Path _path;
    void* _handle;
};

}