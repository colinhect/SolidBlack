#pragma once

#include <Hect.h>

using namespace hect;

class Sample
{
public:
    Sample(const std::string& name);

    void initialize(AssetCache& assetCache, Window& window, Renderer& renderer);
    virtual void execute();

protected:
    AssetCache& assetCache();
    Window& window();
    Renderer& renderer();

private:
    AssetCache* _assetCache;
    Window* _window;
    Renderer* _renderer;
};