SUITE(MeshLoading)
{
    TEST(VertexAndIndexCounts)
    {
        AssetCache assetCache(engine->storage());

        Mesh* mesh = assetCache.getHandle<Mesh>("Window.mesh").get();

        CHECK_EQUAL(4, mesh->vertexCount());
        CHECK_EQUAL(6, mesh->indexCount());
        CHECK_EQUAL(false, mesh->isUploaded());
        CHECK(IndexType::UnsignedShort == mesh->indexType());
        CHECK(PrimitiveType::Triangles == mesh->primitiveType());
    }

    TEST(IndexType)
    {
        AssetCache assetCache(engine->storage());

        Mesh* mesh = assetCache.getHandle<Mesh>("IndexType.mesh").get();

        CHECK(IndexType::UnsignedByte == mesh->indexType());
    }

    TEST(PrimitiveType)
    {
        AssetCache assetCache(engine->storage());

        Mesh* mesh = assetCache.getHandle<Mesh>("PrimitiveType.mesh").get();

        CHECK(PrimitiveType::Points == mesh->primitiveType());
    }
}