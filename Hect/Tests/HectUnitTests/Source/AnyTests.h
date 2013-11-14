SUITE(Any)
{
    TEST(HasValue)
    {
        Any a;
        CHECK(!a.hasValue());

        Any b(5);
        CHECK(b.hasValue());
    }

    TEST(IsType)
    {
        Any a;
        CHECK(!a.isType<int>());

        Any b(5);
        CHECK(b.isType<int>());
    }

    TEST(As)
    {
        Any a(5);
        CHECK_EQUAL(5, a.as<int>());
    }

    TEST(AsError)
    {
        Any a(5);

        bool errorThrown = false;
        try
        {
            a.as<double>();
        }
        catch (Error&)
        {
            errorThrown = true;
        }

        CHECK(errorThrown);
    }

    TEST(Copy)
    {
        Any a(5);
        Any b(a);

        CHECK_EQUAL(5, a.as<int>());
        CHECK_EQUAL(5, b.as<int>());
    }

    TEST(Assign)
    {
        Any a(5);
        CHECK_EQUAL(5, a.as<int>());

        a = std::string("Testing");
        CHECK_EQUAL("Testing", a.as<std::string>());
    }
}