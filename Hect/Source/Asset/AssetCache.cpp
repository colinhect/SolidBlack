#include "Hect.h"

using namespace hect;

AssetCache::AssetCache(FileSystem& fileSystem) :
    _fileSystem(fileSystem)
{
}

void AssetCache::clear()
{
    _entries.clear();
}

FileSystem& AssetCache::fileSystem()
{
    return _fileSystem;
}
