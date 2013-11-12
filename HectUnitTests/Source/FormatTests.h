SUITE(Utils)
{
    TEST(Format)
    {
        CHECK_EQUAL("Testing 1, 2, 3...", format("Testing %d, %d, %d...", 1, 2, 3));
    }
}