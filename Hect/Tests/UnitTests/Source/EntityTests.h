SUITE(Entity)
{
    TEST(NullConstructor)
    {
        Entity a;
        CHECK(a.isNull());
    }
}
