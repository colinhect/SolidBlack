VertexLayout createVetexLayout()
{
    VertexAttribute::Array attributes;
    attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3));
    attributes.push_back(VertexAttribute(VertexAttribute::Normal, VertexAttribute::Float, 3));

    return VertexLayout(attributes);
}

SUITE(MeshBuilder)
{
    TEST(EmptyMesh)
    {
        Mesh mesh(createVetexLayout(), PrimitiveType::Triangles, IndexType::UnsignedByte);
        MeshBuilder meshBuilder(mesh);

        CHECK_EQUAL(0, mesh.vertexCount());
        CHECK_EQUAL(0, mesh.indexCount());
    }

    TEST(AddVertexWithoutAttributeData)
    {
        Mesh mesh(createVetexLayout(), PrimitiveType::Triangles, IndexType::UnsignedByte);
        MeshBuilder meshBuilder(mesh);
        meshBuilder.addVertex();

        CHECK_EQUAL(1, mesh.vertexCount());
        CHECK_EQUAL(0, mesh.indexCount());

        const float* vertexData = (const float*)&mesh.vertexData()[0];
        CHECK_EQUAL(0.0f, vertexData[ 0]);
        CHECK_EQUAL(0.0f, vertexData[ 1]);
        CHECK_EQUAL(0.0f, vertexData[ 2]);
        CHECK_EQUAL(0.0f, vertexData[ 3]);
        CHECK_EQUAL(0.0f, vertexData[ 4]);
        CHECK_EQUAL(0.0f, vertexData[ 5]);
    }

    TEST(SetAttributeDataOfSameTypeAndCardinality)
    {
        Mesh mesh(createVetexLayout(), PrimitiveType::Triangles, IndexType::UnsignedByte);
        MeshBuilder meshBuilder(mesh);
        meshBuilder.addVertex();
        meshBuilder.setAttributeData(VertexAttribute::Position, Vector3<float>(1.0f, 2.0f, 3.0f));

        CHECK_EQUAL(1, mesh.vertexCount());
        CHECK_EQUAL(0, mesh.indexCount());

        const float* vertexData = (const float*)&mesh.vertexData()[0];
        CHECK_EQUAL(1.0f, vertexData[ 0]);
        CHECK_EQUAL(2.0f, vertexData[ 1]);
        CHECK_EQUAL(3.0f, vertexData[ 2]);
        CHECK_EQUAL(0.0f, vertexData[ 3]);
        CHECK_EQUAL(0.0f, vertexData[ 4]);
        CHECK_EQUAL(0.0f, vertexData[ 5]);
    }

    TEST(SetAttributeDataOfSameTypeAndLarger)
    {
        Mesh mesh(createVetexLayout(), PrimitiveType::Triangles, IndexType::UnsignedByte);
        MeshBuilder meshBuilder(mesh);
        meshBuilder.addVertex();
        meshBuilder.setAttributeData(VertexAttribute::Position, Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f));

        CHECK_EQUAL(1, mesh.vertexCount());
        CHECK_EQUAL(0, mesh.indexCount());

        const float* vertexData = (const float*)&mesh.vertexData()[0];
        CHECK_EQUAL(1.0f, vertexData[ 0]);
        CHECK_EQUAL(2.0f, vertexData[ 1]);
        CHECK_EQUAL(3.0f, vertexData[ 2]);
        CHECK_EQUAL(0.0f, vertexData[ 3]);
        CHECK_EQUAL(0.0f, vertexData[ 4]);
        CHECK_EQUAL(0.0f, vertexData[ 5]);
    }

    TEST(SetAttributeDataOfSameTypeAndSmaller)
    {
        Mesh mesh(createVetexLayout(), PrimitiveType::Triangles, IndexType::UnsignedByte);
        MeshBuilder meshBuilder(mesh);
        meshBuilder.addVertex();
        meshBuilder.setAttributeData(VertexAttribute::Position, Vector2<float>(1.0f, 2.0f));

        CHECK_EQUAL(1, mesh.vertexCount());
        CHECK_EQUAL(0, mesh.indexCount());

        const float* vertexData = (const float*)&mesh.vertexData()[0];
        CHECK_EQUAL(1.0f, vertexData[ 0]);
        CHECK_EQUAL(2.0f, vertexData[ 1]);
        CHECK_EQUAL(0.0f, vertexData[ 2]);
        CHECK_EQUAL(0.0f, vertexData[ 3]);
        CHECK_EQUAL(0.0f, vertexData[ 4]);
        CHECK_EQUAL(0.0f, vertexData[ 5]);
    }

    TEST(SimpleMesh)
    {
        Mesh mesh(createVetexLayout(), PrimitiveType::Triangles, IndexType::UnsignedByte);
        MeshBuilder meshBuilder(mesh);
        meshBuilder.addVertex();
        meshBuilder.setAttributeData(VertexAttribute::Position, Vector3<float>(1.0f, 2.0f, 3.0f));
        meshBuilder.setAttributeData(VertexAttribute::Normal, Vector3<float>(-1.0f, -2.0f, -3.0f));
        meshBuilder.addVertex();
        meshBuilder.setAttributeData(VertexAttribute::Position, Vector3<float>(4.0f, 5.0f, 6.0f));
        meshBuilder.setAttributeData(VertexAttribute::Normal, Vector3<float>(-4.0f, -5.0f, -6.0f));
        meshBuilder.addVertex();
        meshBuilder.setAttributeData(VertexAttribute::Position, Vector3<float>(7.0f, 8.0f, 9.0f));
        meshBuilder.setAttributeData(VertexAttribute::Normal, Vector3<float>(-7.0f, -8.0f, -9.0f));

        meshBuilder.addIndex(0);
        meshBuilder.addIndex(1);
        meshBuilder.addIndex(2);
        meshBuilder.addIndex(0);

        CHECK_EQUAL(3, mesh.vertexCount());
        CHECK_EQUAL(4, mesh.indexCount());

        const float* vertexData = (const float*)&mesh.vertexData()[0];
        CHECK_EQUAL( 1.0f, vertexData[ 0]);
        CHECK_EQUAL( 2.0f, vertexData[ 1]);
        CHECK_EQUAL( 3.0f, vertexData[ 2]);
        CHECK_EQUAL(-1.0f, vertexData[ 3]);
        CHECK_EQUAL(-2.0f, vertexData[ 4]);
        CHECK_EQUAL(-3.0f, vertexData[ 5]);
        CHECK_EQUAL( 4.0f, vertexData[ 6]);
        CHECK_EQUAL( 5.0f, vertexData[ 7]);
        CHECK_EQUAL( 6.0f, vertexData[ 8]);
        CHECK_EQUAL(-4.0f, vertexData[ 9]);
        CHECK_EQUAL(-5.0f, vertexData[10]);
        CHECK_EQUAL(-6.0f, vertexData[11]);
        CHECK_EQUAL( 7.0f, vertexData[12]);
        CHECK_EQUAL( 8.0f, vertexData[13]);
        CHECK_EQUAL( 9.0f, vertexData[14]);
        CHECK_EQUAL(-7.0f, vertexData[15]);
        CHECK_EQUAL(-8.0f, vertexData[16]);
        CHECK_EQUAL(-9.0f, vertexData[17]);

        const uint8_t* indexData = (const uint8_t*)&mesh.indexData()[0];
        CHECK_EQUAL(0, indexData[0]);
        CHECK_EQUAL(1, indexData[1]);
        CHECK_EQUAL(2, indexData[2]);
        CHECK_EQUAL(0, indexData[3]);
    }
}