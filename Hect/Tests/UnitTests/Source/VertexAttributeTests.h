SUITE(VertexAttribute)
{
    TEST(ConstructorAndAccessors)
    {
        VertexAttribute attribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 3);

        CHECK(VertexAttributeSemantic::Position == attribute.semantic());
        CHECK(VertexAttributeType::Float == attribute.type());
        CHECK_EQUAL(3u, attribute.cardinality());
    }

    TEST(Size)
    {
        VertexAttribute attribute(VertexAttributeSemantic::Position, VertexAttributeType::Half, 3);
        CHECK_EQUAL(2u * 3u, attribute.size());

        attribute = VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 3);
        CHECK_EQUAL(4u * 3u, attribute.size());

        attribute = VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 2);
        CHECK_EQUAL(4u * 2u, attribute.size());
    }
}