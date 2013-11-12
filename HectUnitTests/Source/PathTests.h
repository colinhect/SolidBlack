SUITE(Path)
{
    TEST(DefaultConstructor)
    {
        Path path;

        CHECK_EQUAL("", path.toString());
    }

    TEST(ConstructorWithOnePart)
    {
        Path path("Data");

        CHECK_EQUAL("Data", path.toString());
    }

    TEST(ConstructorWithMultipleParts)
    {
        Path path("Data/Internal/Fail.log");

        CHECK_EQUAL("Data/Internal/Fail.log", path.toString());
    }

    TEST(ConstructorWithLeadingSlash)
    {
        Path path("/Data/Internal/Fail.log");

        CHECK_EQUAL("Data/Internal/Fail.log", path.toString());
    }

    TEST(ConstructorWithTrailingSlash)
    {
        Path path("Data/Internal/");

        CHECK_EQUAL("Data/Internal", path.toString());
    }

    TEST(ConstructorWithLeadingAndTrailingSlash)
    {
        Path path("/Data/Internal/");

        CHECK_EQUAL("Data/Internal", path.toString());
    }

    TEST(Extension)
    {
        Path path("Data/Internal/Fail.log");

        CHECK_EQUAL("log", path.extension());
    }

    TEST(NoExtension)
    {
        Path path("Data/Internal/Fail");

        CHECK_EQUAL("", path.extension());
    }

    TEST(Add)
    {
        Path path = Path("Data") + Path("Internal/Fail.log");

        CHECK_EQUAL("Data/Internal/Fail.log", path.toString());
    }

    TEST(AddWithEmptyFirst)
    {
        Path path = Path() + Path("Internal/Fail.log");

        CHECK_EQUAL("Internal/Fail.log", path.toString());
    }

    TEST(AddWithEmptySecond)
    {
        Path path = Path("Data/Internal") + Path();

        CHECK_EQUAL("Data/Internal", path.toString());
    }

    TEST(AddEquals)
    {
        Path path("Data");
        path += "Internal/Fail.log";

        CHECK_EQUAL("Data/Internal/Fail.log", path.toString());
    }

    TEST(AddEqualsFromEmpty)
    {
        Path path;
        path += "Data";
        path += "Internal/Fail.log";

        CHECK_EQUAL("Data/Internal/Fail.log", path.toString());
    }

    TEST(StreamOutput)
    {
        Path path("/Data/Internal/Fail.log");

        std::stringstream ss;
        ss << path;

        CHECK_EQUAL("Data/Internal/Fail.log", ss.str());
    }
}