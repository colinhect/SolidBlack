SUITE(VertexAttribute)
{
    TEST(ConstructorAndAccessors)
    {
        VertexAttribute attribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 3);

        CHECK(VertexAttributeSemantic::Position == attribute.semantic());
        CHECK(VertexAttributeType::Float == attribute.type());
        CHECK_EQUAL(3, attribute.cardinality());
    }

    TEST(Size)
    {
        VertexAttribute attribute(VertexAttributeSemantic::Position, VertexAttributeType::Half, 3);
        CHECK_EQUAL(2 * 3, attribute.size());

        attribute = VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 3);
        CHECK_EQUAL(4 * 3, attribute.size());

        attribute = VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 2);
        CHECK_EQUAL(4 * 2, attribute.size());
    }
}