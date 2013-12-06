SUITE(MeshReader)
{
    TEST(EmptyMesh)
    {
        Mesh mesh(createVetexLayout(), PrimitiveType::Triangles, IndexType::UnsignedByte);
        MeshReader meshReader(mesh);

        CHECK(!meshReader.nextVertex());
        CHECK(!meshReader.nextIndex());
    }

    TEST(ReadAttributeVector3)
    {
        Mesh mesh(createVetexLayout(), PrimitiveType::Triangles, IndexType::UnsignedByte);

        {
            MeshWriter meshWriter(mesh);
            meshWriter.addVertex();
            meshWriter.writeAttributeData(VertexAttributeSemantic::Position, Vector3<>(1, 2, 3));
            meshWriter.writeAttributeData(VertexAttributeSemantic::Normal, Vector3<>(4, 5, 6));
            meshWriter.addVertex();
            meshWriter.writeAttributeData(VertexAttributeSemantic::Position, Vector3<>(7, 8, 9));
            meshWriter.writeAttributeData(VertexAttributeSemantic::Normal, Vector3<>(10, 11, 12));
            meshWriter.addVertex();
            meshWriter.writeAttributeData(VertexAttributeSemantic::Position, Vector3<>(13, 14, 15));
            meshWriter.writeAttributeData(VertexAttributeSemantic::Normal, Vector3<>(16, 17, 18));
        }

        Vector3<> value;
        MeshReader meshReader(mesh);

        CHECK(meshReader.nextVertex());

        value = meshReader.readAttributeVector3(VertexAttributeSemantic::Position);
        CHECK_EQUAL(1, value.x);
        CHECK_EQUAL(2, value.y);
        CHECK_EQUAL(3, value.z);

        value = meshReader.readAttributeVector3(VertexAttributeSemantic::Normal);
        CHECK_EQUAL(4, value.x);
        CHECK_EQUAL(5, value.y);
        CHECK_EQUAL(6, value.z);

        CHECK(meshReader.nextVertex());

        value = meshReader.readAttributeVector3(VertexAttributeSemantic::Position);
        CHECK_EQUAL(7, value.x);
        CHECK_EQUAL(8, value.y);
        CHECK_EQUAL(9, value.z);

        value = meshReader.readAttributeVector3(VertexAttributeSemantic::Normal);
        CHECK_EQUAL(10, value.x);
        CHECK_EQUAL(11, value.y);
        CHECK_EQUAL(12, value.z);

        CHECK(meshReader.nextVertex());

        value = meshReader.readAttributeVector3(VertexAttributeSemantic::Position);
        CHECK_EQUAL(13, value.x);
        CHECK_EQUAL(14, value.y);
        CHECK_EQUAL(15, value.z);

        value = meshReader.readAttributeVector3(VertexAttributeSemantic::Normal);
        CHECK_EQUAL(16, value.x);
        CHECK_EQUAL(17, value.y);
        CHECK_EQUAL(18, value.z);

        CHECK(!meshReader.nextVertex());
    }

    TEST(ReadIndexByte)
    {
        Mesh mesh(createVetexLayout(), PrimitiveType::Triangles, IndexType::UnsignedByte);

        {
            MeshWriter meshWriter(mesh);
            meshWriter.addIndex(0);
            meshWriter.addIndex(1);
            meshWriter.addIndex(2);
        }

        Vector3<> value;
        MeshReader meshReader(mesh);

        CHECK(meshReader.nextIndex());
        CHECK_EQUAL(0, meshReader.readIndexByte());

        CHECK(meshReader.nextIndex());
        CHECK_EQUAL(1, meshReader.readIndexByte());

        CHECK(meshReader.nextIndex());
        CHECK_EQUAL(2, meshReader.readIndexByte());

        CHECK(!meshReader.nextIndex());
    }
}