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

private:
    FileWriteStream(const Path& path);

    Path _path;
    void* _handle;
};

}