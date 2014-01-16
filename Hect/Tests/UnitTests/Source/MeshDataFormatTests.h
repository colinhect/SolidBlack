SUITE(MeshDataFormat)
{
    TEST(VertexAndIndexCounts)
    {
        FileSystem fileSystem;
        fileSystem.addDataSource("Data");

        AssetCache assetCache(fileSystem);

        Mesh& mesh = assetCache.get<Mesh>("Window.mesh");

        CHECK_EQUAL(4, mesh.vertexCount());
        CHECK_EQUAL(6, mesh.indexCount());
        CHECK_EQUAL(false, mesh.isUploaded());
        CHECK(IndexType::UnsignedShort == mesh.indexType());
        CHECK(PrimitiveType::Triangles == mesh.primitiveType());
    }

    TEST(IndexType)
    {
        FileSystem fileSystem;
        fileSystem.addDataSource("Data");

        AssetCache assetCache(fileSystem);

        Mesh& mesh = assetCache.get<Mesh>("IndexType.mesh");

        CHECK(IndexType::UnsignedByte == mesh.indexType());
    }

    TEST(PrimitiveType)
    {
        FileSystem fileSystem;
        fileSystem.addDataSource("Data");

        AssetCache assetCache(fileSystem);

        Mesh& mesh = assetCache.get<Mesh>("PrimitiveType.mesh");

        CHECK(PrimitiveType::Points == mesh.primitiveType());
    }
}