#include "Hect.h"

using namespace hect;

AssetCache::AssetCache(Storage& storage) :
    _storage(storage)
{
}

Storage& AssetCache::storage()
{
    return _storage;
}
