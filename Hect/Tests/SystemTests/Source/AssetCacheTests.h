SUITE(AssetCache)
{
    TEST(GetAsset)
    {
        AssetCache assetCache(engine->storage());

        AssetHandle<ShaderModule> a = assetCache.getHandle<ShaderModule>("Window.vert");

        CHECK(a.get());
    }

    TEST(GetNonExistingAsset)
    {
        AssetCache assetCache(engine->storage());

        AssetHandle<ShaderModule> a = assetCache.getHandle<ShaderModule>("DoesNotExist");

        bool errorThrown = false;
        try
        {
            a.get();
        }
        catch (Error&)
        {
            errorThrown = true;
        }

        CHECK(errorThrown);
    }

    TEST(HandlesShareAssetEntry)
    {
        AssetCache assetCache(engine->storage());

        AssetHandle<ShaderModule> a = assetCache.getHandle<ShaderModule>("Window.vert");
        AssetHandle<ShaderModule> b = assetCache.getHandle<ShaderModule>("Window.vert");

        CHECK_EQUAL(a.get(), b.get());
    }

    TEST(GetSeparateAssets)
    {
        AssetCache assetCache(engine->storage());

        AssetHandle<ShaderModule> a = assetCache.getHandle<ShaderModule>("Window.vert");
        AssetHandle<ShaderModule> b = assetCache.getHandle<ShaderModule>("Window.frag");

        CHECK(a.get() != b.get());
        CHECK(ShaderModuleType::Vertex == a.get()->type());
        CHECK(ShaderModuleType::Pixel == b.get()->type());
    }
}