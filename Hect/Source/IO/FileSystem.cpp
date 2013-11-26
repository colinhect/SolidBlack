#include "Hect.h"

#include <physfs.h>

#ifdef HECT_WINDOWS
#include <Windows.h>
#endif

namespace hect
{
FileSystem* _fileSystem = nullptr;
}

using namespace hect;

FileSystem::FileSystem()
{
    // Prevent multiple instances
    if (_fileSystem)
    {
        throw Error("Attempt to instantiate multiple file system instances");
    }
    _fileSystem = this;

    if (!PHYSFS_init(nullptr))
    {
        throw Error(format("Failed to initialize file system: %s", PHYSFS_getLastError()));
    }
}

FileSystem::~FileSystem()
{
    if (!PHYSFS_deinit())
    {
        throw Error(format("Failed to shutdown file system: %s", PHYSFS_getLastError()));
    }

    _fileSystem = nullptr;
}

Path FileSystem::workingDirectory() const
{
#ifdef HECT_WINDOWS
    char path[2048];
    GetCurrentDirectory(2048, path);
    return _convertPath(path);
#endif
}

Path FileSystem::userDirectory() const
{
    return _convertPath(PHYSFS_getUserDir());
}

void FileSystem::setWriteDirectory(const Path& path)
{
    if (!PHYSFS_setWriteDir(path.toString().c_str()))
    {
        throw Error(format("Failed to set write directory: %s", PHYSFS_getLastError()));
    }
}

void FileSystem::addDataSource(const Path& path)
{
    if (!PHYSFS_mount(path.toString().c_str(), NULL, 0))
    {
        throw Error(format("Failed to add data source: %s", PHYSFS_getLastError()));
    }
}

FileReadStream FileSystem::openFileForRead(const Path& path) const
{
    return FileReadStream(path);
}

FileWriteStream FileSystem::openFileForWrite(const Path& path)
{
    return FileWriteStream(path);
}

void FileSystem::createDirectory(const Path& path)
{
    if (!PHYSFS_mkdir(path.toString().c_str()))
    {
        throw Error(format("Failed to create directory: %s", PHYSFS_getLastError()));
    }
}

void FileSystem::remove(const Path& path)
{
    if (!PHYSFS_delete(path.toString().c_str()))
    {
        throw Error(format("Failed to remove directory: %s", PHYSFS_getLastError()));
    }
}

bool FileSystem::exists(const Path& path) const
{
    return PHYSFS_exists(path.toString().c_str()) != 0;
}

Path FileSystem::_convertPath(const char* rawPath) const
{
    std::string delimiter(PHYSFS_getDirSeparator());
    std::string string(rawPath);

    size_t start = 0;
    while((start = string.find(delimiter, start)) != std::string::npos)
    {
        string.replace(start, delimiter.length(), "/");
        start += 1;
    }

    return Path(string);
}