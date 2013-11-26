#include "Hect.h"

using namespace hect;

AssetCache::AssetCache(FileSystem& fileSystem) :
    _fileSystem(fileSystem)
{
}

FileSystem& AssetCache::fileSystem()
{
    return _fileSystem;
}
