#include "Hect.h"

#include <physfs.h>

using namespace hect;

FileWriteStream::~FileWriteStream()
{
    if (_handle)
    {
        if (!PHYSFS_close((PHYSFS_File*)_handle))
        {
            throw Error(format("Failed to close file for writing: %s", PHYSFS_getLastError()));
        }
    }
}

void FileWriteStream::writeBytes(const uint8_t* bytes, size_t byteCount)
{
    assert(bytes);

    auto file = (PHYSFS_File*)_handle;
    PHYSFS_sint64 result = PHYSFS_write(file, bytes, 1, (PHYSFS_uint32)byteCount);
    if (result != (PHYSFS_sint64)byteCount)
    {
        throw Error(format("Failed to write to file: %s", PHYSFS_getLastError()));
    }
}

FileWriteStream::FileWriteStream(const Path& path) :
    _path(path),
    _handle(nullptr)
{
    std::stringstream ss;
    ss << path;

    _handle = PHYSFS_openWrite(ss.str().c_str());
    if (!_handle)
    {
        throw Error(format("Failed to open file for writing: %s", PHYSFS_getLastError()));
    }
}