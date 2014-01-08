#include "Sample.h"

Sample::Sample(const std::string& name) :
    _assetCache(nullptr),
    _window(nullptr),
    _renderer(nullptr)
{
}

void Sample::initialize(AssetCache& assetCache, Window& window, Renderer& renderer)
{
    _assetCache = &assetCache;
    _window = &window;
    _renderer = &renderer;
}

void Sample::execute()
{
}

AssetCache& Sample::assetCache()
{
    return *_assetCache;
}

Window& Sample::window()
{
    return *_window;
}

Renderer& Sample::renderer()
{
    return *_renderer;
}