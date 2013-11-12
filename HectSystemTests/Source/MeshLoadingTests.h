SUITE(MeshLoading)
{
    TEST(VertexAndIndexCounts)
    {
        AssetCache assetCache(engine->storage());

        Mesh* mesh = assetCache.getHandle<Mesh>("Screen.mesh").get();

        CHECK_EQUAL(4, mesh->vertexCount());
        CHECK_EQUAL(6, mesh->indexCount());
        CHECK_EQUAL(false, mesh->isUploaded());
        CHECK_EQUAL(Mesh::Unsigned16, mesh->indexType());
        CHECK_EQUAL(Mesh::Triangles, mesh->primitiveType());
    }

    TEST(IndexType)
    {
        AssetCache assetCache(engine->storage());

        Mesh* mesh = assetCache.getHandle<Mesh>("IndexType.mesh").get();

        CHECK_EQUAL(Mesh::Unsigned8, mesh->indexType());
    }

    TEST(PrimitiveType)
    {
        AssetCache assetCache(engine->storage());

        Mesh* mesh = assetCache.getHandle<Mesh>("PrimitiveType.mesh").get();

        CHECK_EQUAL(Mesh::Points, mesh->primitiveType());
    }
}