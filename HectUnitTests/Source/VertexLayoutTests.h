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
        attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3));
        attributes.push_back(VertexAttribute(VertexAttribute::Normal, VertexAttribute::Half, 3));

        VertexLayout vertexLayout(attributes);
        CHECK_EQUAL(2, vertexLayout.attributes().size());
    }

    TEST(AttributeIndexing)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3));
        attributes.push_back(VertexAttribute(VertexAttribute::Normal, VertexAttribute::Half, 3));

        VertexLayout vertexLayout(attributes);

        CHECK_EQUAL(VertexAttribute::Position, vertexLayout.attributes()[0].semantic());
        CHECK_EQUAL(VertexAttribute::Normal, vertexLayout.attributes()[1].semantic());
    }

    TEST(AttributeOffsets)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3));
        attributes.push_back(VertexAttribute(VertexAttribute::Normal, VertexAttribute::Half, 3));

        VertexLayout vertexLayout(attributes);

        CHECK_EQUAL(0, vertexLayout.attributes()[0].offset());
        CHECK_EQUAL(vertexLayout.attributes()[0].size(), vertexLayout.attributes()[1].offset());
    }

    TEST(AttributeWithSemantic)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 4));
        attributes.push_back(VertexAttribute(VertexAttribute::Normal, VertexAttribute::Half, 3));

        VertexLayout vertexLayout(attributes);

        CHECK_EQUAL(4, vertexLayout.attributeWithSemantic(VertexAttribute::Position)->cardinality());
        CHECK_EQUAL(3, vertexLayout.attributeWithSemantic(VertexAttribute::Normal)->cardinality());
    }

    TEST(AttributeWithSemanticNegative)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3));
        attributes.push_back(VertexAttribute(VertexAttribute::Normal, VertexAttribute::Half, 3));

        VertexLayout vertexLayout(attributes);

        CHECK(!vertexLayout.attributeWithSemantic(VertexAttribute::Color));
    }

    TEST(VertexSize)
    {
        VertexAttribute::Array attributes;
        attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3));
        attributes.push_back(VertexAttribute(VertexAttribute::Normal, VertexAttribute::Half, 3));

        VertexLayout vertexLayout(attributes);

        CHECK_EQUAL(4 * 3 + 2 * 3, vertexLayout.vertexSize());
    }
}