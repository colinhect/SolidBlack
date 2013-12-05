SUITE(VertexLayout)
{
    TEST(DefaultConstructor)
    {
        VertexLayout vertexLayout;
        CHECK_EQUAL(0, vertexLayout.attributes().size());
    }

    TEST(AttributeConstructor)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 3));
        attributes.push_back(VertexAttribute(VertexAttributeSemantic::Normal, VertexAttributeType::Half, 3));

        VertexLayout vertexLayout(attributes);
        CHECK_EQUAL(2, vertexLayout.attributes().size());
    }

    TEST(AttributeIndexing)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 3));
        attributes.push_back(VertexAttribute(VertexAttributeSemantic::Normal, VertexAttributeType::Half, 3));

        VertexLayout vertexLayout(attributes);

        CHECK(VertexAttributeSemantic::Position == vertexLayout.attributes()[0].semantic());
        CHECK(VertexAttributeSemantic::Normal == vertexLayout.attributes()[1].semantic());
    }

    TEST(AttributeOffsets)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 3));
        attributes.push_back(VertexAttribute(VertexAttributeSemantic::Normal, VertexAttributeType::Half, 3));

        VertexLayout vertexLayout(attributes);

        CHECK_EQUAL(0u, vertexLayout.attributes()[0].offset());
        CHECK_EQUAL(vertexLayout.attributes()[0].size(), vertexLayout.attributes()[1].offset());
    }

    TEST(AttributeWithSemantic)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 4));
        attributes.push_back(VertexAttribute(VertexAttributeSemantic::Normal, VertexAttributeType::Half, 3));

        VertexLayout vertexLayout(attributes);

        CHECK_EQUAL(4u, vertexLayout.attributeWithSemantic(VertexAttributeSemantic::Position)->cardinality());
        CHECK_EQUAL(3u, vertexLayout.attributeWithSemantic(VertexAttributeSemantic::Normal)->cardinality());
    }

    TEST(AttributeWithSemanticNegative)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 3));
        attributes.push_back(VertexAttribute(VertexAttributeSemantic::Normal, VertexAttributeType::Half, 3));

        VertexLayout vertexLayout(attributes);

        CHECK(!vertexLayout.attributeWithSemantic(VertexAttributeSemantic::Color));
    }

    TEST(VertexSize)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 3));
        attributes.push_back(VertexAttribute(VertexAttributeSemantic::Normal, VertexAttributeType::Half, 3));

        VertexLayout vertexLayout(attributes);

        CHECK_EQUAL(4u * 3u + 2u * 3u, vertexLayout.vertexSize());
    }
}