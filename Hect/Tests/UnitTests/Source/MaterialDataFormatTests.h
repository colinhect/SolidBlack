SUITE(MaterialDataFormat)
{
    TEST(NoBase)
    {
        FileSystem fileSystem;
        fileSystem.addDataSource("Data");

        AssetCache assetCache(fileSystem);

        Material* base = assetCache.getHandle<Material>("Base.material").get();
        Shader* window = assetCache.getHandle<Shader>("Window.shader").get();

        CHECK_EQUAL(1, base->techniques().size());
        CHECK_EQUAL(1, base->techniques()[0].passes().size());

        const Pass& pass = base->techniques()[0].passes()[0];

        CHECK_EQUAL(window, pass.shader().get());

        const RenderMode& renderMode = pass.renderMode();
        CHECK(renderMode.isStateEnabled(RenderState::Blend));
        CHECK(!renderMode.isStateEnabled(RenderState::DepthTest));
        CHECK(!renderMode.isStateEnabled(RenderState::CullFace));
        CHECK(BlendFactor::Zero == renderMode.sourceBlendFactor());
        CHECK(BlendFactor::OneMinusSourceAlpha == renderMode.destBlendFactor());
    }

    TEST(WithBase)
    {
        FileSystem fileSystem;
        fileSystem.addDataSource("Data");

        AssetCache assetCache(fileSystem);

        Material* test = assetCache.getHandle<Material>("Test.material").get();
        Material* base = assetCache.getHandle<Material>("Base.material").get();

        CHECK_EQUAL(base->techniques().size(), test->techniques().size());
        CHECK_EQUAL(base->techniques()[0].passes().size(), test->techniques()[0].passes().size());

        const Pass& basePass = base->techniques()[0].passes()[0];
        const Pass& pass = test->techniques()[0].passes()[0];

        CHECK_EQUAL(basePass.shader().get(), pass.shader().get());

        const RenderMode& renderMode = pass.renderMode();
        CHECK(!renderMode.isStateEnabled(RenderState::Blend));
        CHECK(!renderMode.isStateEnabled(RenderState::DepthTest));
        CHECK(renderMode.isStateEnabled(RenderState::CullFace));
        CHECK(BlendFactor::Zero == renderMode.sourceBlendFactor());
        CHECK(BlendFactor::OneMinusSourceAlpha == renderMode.destBlendFactor());
    }
}