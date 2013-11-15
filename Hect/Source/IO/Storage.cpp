#include "Hect.h"

#include <physfs.h>

#ifdef HECT_WINDOWS
#include <Windows.h>
#endif

namespace hect
{
Storage* _storage = nullptr;
}

using namespace hect;

Storage::Storage()
{
    // Prevent multiple instances
    if (_storage)
    {
        throw Error("Attempt to instantiate multiple storage instances");
    }
    _storage = this;

    if (!PHYSFS_init(nullptr))
    {
        throw Error(format("Failed to initialize access to persistant storage: %s", PHYSFS_getLastError()));
    }
}

Storage::~Storage()
{
    if (!PHYSFS_deinit())
    {
        throw Error(format("Failed to shutdown access to persistant storage: %s", PHYSFS_getLastError()));
    }

    _storage = nullptr;
}

Path Storage::workingDirectory() const
{
#ifdef HECT_WINDOWS
    char path[2048];
    GetCurrentDirectory(2048, path);
    return _convertPath(path);
#endif
}

Path Storage::userDirectory() const
{
    return _convertPath(PHYSFS_getUserDir());
}

void Storage::setWriteDirectory(const Path& path)
{
    if (!PHYSFS_setWriteDir(path.toString().c_str()))
    {
        throw Error(format("Failed to set write directory: %s", PHYSFS_getLastError()));
    }
}

void Storage::addDataSource(const Path& path)
{
    if (!PHYSFS_mount(path.toString().c_str(), NULL, 0))
    {
        throw Error(format("Failed to add data source: %s", PHYSFS_getLastError()));
    }
}

FileReadStream Storage::openFileForRead(const Path& path) const
{
    return FileReadStream(path);
}

FileWriteStream Storage::openFileForWrite(const Path& path)
{
    return FileWriteStream(path);
}

void Storage::createDirectory(const Path& path)
{
    if (!PHYSFS_mkdir(path.toString().c_str()))
    {
        throw Error(format("Failed to create directory: %s", PHYSFS_getLastError()));
    }
}

void Storage::remove(const Path& path)
{
    if (!PHYSFS_delete(path.toString().c_str()))
    {
        throw Error(format("Failed to remove directory: %s", PHYSFS_getLastError()));
    }
}

bool Storage::exists(const Path& path) const
{
    return PHYSFS_exists(path.toString().c_str()) != 0;
}

Path Storage::_convertPath(const char* rawPath) const
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