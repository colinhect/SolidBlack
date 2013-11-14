SUITE(Mesh)
{
    TEST(DefaultConstructor)
    {
        Mesh mesh;

        const VertexLayout& meshVertexLayout = mesh.vertexLayout();
        CHECK_EQUAL(VertexAttribute::Position, meshVertexLayout.attributes()[0].semantic());
        CHECK_EQUAL(Mesh::Triangles, mesh.primitiveType());
        CHECK_EQUAL(Mesh::UnsignedShort, mesh.indexType());
    }

    TEST(Constructor)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3));
        attributes.push_back(VertexAttribute(VertexAttribute::Normal, VertexAttribute::Half, 3));

        VertexLayout vertexLayout(attributes);

        Mesh mesh(vertexLayout, Mesh::Triangles, Mesh::UnsignedByte);

        const VertexLayout& meshVertexLayout = mesh.vertexLayout();
        CHECK_EQUAL(2, meshVertexLayout.attributes().size());
        CHECK_EQUAL(VertexAttribute::Position, meshVertexLayout.attributes()[0].semantic());
        CHECK_EQUAL(VertexAttribute::Float, meshVertexLayout.attributes()[0].type());
        CHECK_EQUAL(3, meshVertexLayout.attributes()[0].cardinality());

        CHECK_EQUAL(Mesh::Triangles, mesh.primitiveType());
        CHECK_EQUAL(Mesh::UnsignedByte, mesh.indexType());
    }

    TEST(SetVertexData)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3));

        VertexLayout vertexLayout(attributes);

        Mesh mesh(vertexLayout, Mesh::Triangles, Mesh::UnsignedByte);

        const float rawVertexData[9] =
        {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };
        std::vector<uint8_t> vertexData(sizeof(float) * 9, 0);
        std::memcpy(&vertexData[0], rawVertexData, sizeof(float) * 9);

        mesh.setVertexData(vertexData);

        CHECK_EQUAL(3, mesh.vertexCount());
    }

    TEST(GetVertexData)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3));

        VertexLayout vertexLayout(attributes);

        Mesh mesh(vertexLayout, Mesh::Triangles, Mesh::UnsignedByte);

        const float rawOriginalVertexData[9] =
        {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };
        std::vector<uint8_t> originalVertexData(sizeof(float) * 9, 0);
        std::memcpy(&originalVertexData[0], rawOriginalVertexData, sizeof(float) * 9);

        mesh.setVertexData(originalVertexData);

        const float* vertexData = (const float*)&mesh.vertexData()[0];

        CHECK_EQUAL(1.0f, vertexData[0]);
        CHECK_EQUAL(0.0f, vertexData[1]);
        CHECK_EQUAL(0.0f, vertexData[2]);
        CHECK_EQUAL(0.0f, vertexData[3]);
        CHECK_EQUAL(1.0f, vertexData[4]);
        CHECK_EQUAL(0.0f, vertexData[5]);
        CHECK_EQUAL(0.0f, vertexData[6]);
        CHECK_EQUAL(0.0f, vertexData[7]);
        CHECK_EQUAL(1.0f, vertexData[8]);
    }

    TEST(SetIndexData)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3));

        VertexLayout vertexLayout(attributes);

        Mesh mesh(vertexLayout, Mesh::Triangles, Mesh::UnsignedByte);

        std::vector<uint8_t> indexData;
        indexData.push_back(0);
        indexData.push_back(1);
        indexData.push_back(2);
        indexData.push_back(2);
        indexData.push_back(3);
        indexData.push_back(0);

        mesh.setIndexData(indexData);

        CHECK_EQUAL(6, mesh.indexCount());
    }

    TEST(GetIndexDataUnsignedByte)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3));

        VertexLayout vertexLayout(attributes);

        Mesh mesh(vertexLayout, Mesh::Triangles, Mesh::UnsignedByte);

        std::vector<uint8_t> originalIndexData;
        originalIndexData.push_back(0);
        originalIndexData.push_back(1);
        originalIndexData.push_back(2);
        originalIndexData.push_back(2);
        originalIndexData.push_back(3);
        originalIndexData.push_back(0);

        mesh.setIndexData(originalIndexData);
        CHECK_EQUAL(6, mesh.indexCount());

        const uint8_t* indexData = &mesh.indexData()[0];

        CHECK_EQUAL(0, indexData[0]);
        CHECK_EQUAL(1, indexData[1]);
        CHECK_EQUAL(2, indexData[2]);
        CHECK_EQUAL(2, indexData[3]);
        CHECK_EQUAL(3, indexData[4]);
        CHECK_EQUAL(0, indexData[5]);
    }

    TEST(SetVertexLayout)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttribute::Tangent, VertexAttribute::Float, 3));

        VertexLayout vertexLayout(attributes);

        Mesh mesh;
        mesh.setVertexLayout(vertexLayout);

        const VertexLayout& meshVertexLayout = mesh.vertexLayout();
        CHECK_EQUAL(VertexAttribute::Tangent, meshVertexLayout.attributes()[0].semantic());
    }

    TEST(SetVertexLayoutWithVertexData)
    {
        Mesh mesh;
        mesh.setVertexData(std::vector<uint8_t>(10, 0));

        bool errorThrown = false;
        try
        {
            mesh.setVertexLayout(VertexLayout());
        }
        catch (Error&)
        {
            errorThrown = true;
        }

        CHECK(errorThrown);
    }

    TEST(SetIndexType)
    {
        Mesh mesh;
        mesh.setIndexType(Mesh::UnsignedByte);

        CHECK_EQUAL(Mesh::UnsignedByte, mesh.indexType());
    }

    TEST(SetIndexTypeWithIndexData)
    {
        Mesh mesh;

        mesh.setIndexData(std::vector<uint8_t>(10, 0));

        bool errorThrown = false;
        try
        {
            mesh.setIndexType(Mesh::UnsignedByte);
        }
        catch (Error&)
        {
            errorThrown = true;
        }

        CHECK(errorThrown);
    }
}