SUITE(VertexAttribute)
{
    TEST(ConstructorAndAccessors)
    {
        VertexAttribute attribute(VertexAttribute::Position, VertexAttribute::Float32, 3);

        CHECK_EQUAL(VertexAttribute::Position, attribute.semantic());
        CHECK_EQUAL(VertexAttribute::Float32, attribute.type());
        CHECK_EQUAL(3, attribute.cardinality());
    }

    TEST(Size)
    {
        VertexAttribute attribute(VertexAttribute::Position, VertexAttribute::Float16, 3);
        CHECK_EQUAL(2 * 3, attribute.size());

        attribute = VertexAttribute(VertexAttribute::Position, VertexAttribute::Float32, 3);
        CHECK_EQUAL(4 * 3, attribute.size());

        attribute = VertexAttribute(VertexAttribute::Position, VertexAttribute::Float32, 2);
        CHECK_EQUAL(4 * 2, attribute.size());
    }
}