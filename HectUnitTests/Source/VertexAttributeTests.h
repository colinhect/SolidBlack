SUITE(VertexAttribute)
{
    TEST(ConstructorAndAccessors)
    {
        VertexAttribute attribute(VertexAttribute::Position, VertexAttribute::Float, 3);

        CHECK_EQUAL(VertexAttribute::Position, attribute.semantic());
        CHECK_EQUAL(VertexAttribute::Float, attribute.type());
        CHECK_EQUAL(3, attribute.cardinality());
    }

    TEST(Size)
    {
        VertexAttribute attribute(VertexAttribute::Position, VertexAttribute::Half, 3);
        CHECK_EQUAL(2 * 3, attribute.size());

        attribute = VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3);
        CHECK_EQUAL(4 * 3, attribute.size());

        attribute = VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 2);
        CHECK_EQUAL(4 * 2, attribute.size());
    }
}