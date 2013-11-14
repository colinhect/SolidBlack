SUITE(AssetCache)
{
    TEST(GetAsset)
    {
        AssetCache assetCache(engine->storage());

        AssetHandle<ShaderModule> a = assetCache.getHandle<ShaderModule>("Screen.vert");

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

        AssetHandle<ShaderModule> a = assetCache.getHandle<ShaderModule>("Screen.vert");
        AssetHandle<ShaderModule> b = assetCache.getHandle<ShaderModule>("Screen.vert");

        CHECK_EQUAL(a.get(), b.get());
    }

    TEST(GetSeparateAssets)
    {
        AssetCache assetCache(engine->storage());

        AssetHandle<ShaderModule> a = assetCache.getHandle<ShaderModule>("Screen.vert");
        AssetHandle<ShaderModule> b = assetCache.getHandle<ShaderModule>("Screen.frag");

        CHECK(a.get() != b.get());
        CHECK_EQUAL(ShaderModule::Vertex, a.get()->type());
        CHECK_EQUAL(ShaderModule::Pixel, b.get()->type());
    }
}