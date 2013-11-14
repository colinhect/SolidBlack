SUITE(MaterialLoading)
{
    TEST(NoBase)
    {
        AssetCache assetCache(engine->storage());

        Material* base = assetCache.getHandle<Material>("Base.material").get();
        Shader* screen = assetCache.getHandle<Shader>("Screen.shader").get();

        CHECK_EQUAL(1, base->techniques().size());
        CHECK_EQUAL(1, base->techniques()[0].passes().size());

        const Pass& pass = base->techniques()[0].passes()[0];

        CHECK_EQUAL(screen, pass.shader().get());

        const RenderMode& renderMode = pass.renderMode();
        CHECK(renderMode.isStateEnabled(RenderMode::Blend));
        CHECK(!renderMode.isStateEnabled(RenderMode::DepthTest));
        CHECK(!renderMode.isStateEnabled(RenderMode::CullFace));
        CHECK_EQUAL(RenderMode::Zero, renderMode.sourceBlendFactor());
        CHECK_EQUAL(RenderMode::OneMinusSourceAlpha, renderMode.destBlendFactor());
    }

    TEST(WithBase)
    {
        AssetCache assetCache(engine->storage());

        Material* test = assetCache.getHandle<Material>("Test.material").get();
        Material* base = assetCache.getHandle<Material>("Base.material").get();

        CHECK_EQUAL(base->techniques().size(), test->techniques().size());
        CHECK_EQUAL(base->techniques()[0].passes().size(), test->techniques()[0].passes().size());

        const Pass& basePass = base->techniques()[0].passes()[0];
        const Pass& pass = test->techniques()[0].passes()[0];

        CHECK_EQUAL(basePass.shader().get(), pass.shader().get());

        const RenderMode& renderMode = pass.renderMode();
        CHECK(!renderMode.isStateEnabled(RenderMode::Blend));
        CHECK(!renderMode.isStateEnabled(RenderMode::DepthTest));
        CHECK(renderMode.isStateEnabled(RenderMode::CullFace));
        CHECK_EQUAL(RenderMode::Zero, renderMode.sourceBlendFactor());
        CHECK_EQUAL(RenderMode::OneMinusSourceAlpha, renderMode.destBlendFactor());
    }
}