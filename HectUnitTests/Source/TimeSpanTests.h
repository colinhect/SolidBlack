SUITE(TimeSpan)
{
    TEST(FromMicroseconds)
    {
        TimeSpan t = TimeSpan::fromMicroseconds(1000);
        CHECK_EQUAL(1000, t.microseconds());
    }

    TEST(FromMilliseconds)
    {
        TimeSpan t = TimeSpan::fromMilliseconds(1000);
        CHECK_EQUAL(1000000, t.microseconds());
    }

    TEST(FromSeconds)
    {
        TimeSpan t = TimeSpan::fromSeconds(0.001);
        CHECK_EQUAL(1000, t.microseconds());
    }

    TEST(Milliseconds)
    {
        TimeSpan t = TimeSpan::fromMicroseconds(1000);
        CHECK_EQUAL(1, t.milliseconds());
    }

    TEST(Seconds)
    {
        TimeSpan t = TimeSpan::fromMicroseconds(1000);
        CHECK_CLOSE(0.001, t.seconds(), epsilon);
    }

    TEST(Add)
    {
        TimeSpan t = TimeSpan::fromMicroseconds(10) + TimeSpan::fromMicroseconds(5);
        CHECK_EQUAL(15, t.microseconds());
    }

    TEST(AddEquals)
    {
        TimeSpan t = TimeSpan::fromMicroseconds(10);
        t += TimeSpan::fromMicroseconds(5);
        CHECK_EQUAL(15, t.microseconds());
    }

    TEST(Subtract)
    {
        TimeSpan t = TimeSpan::fromMicroseconds(10) - TimeSpan::fromMicroseconds(5);
        CHECK_EQUAL(5, t.microseconds());
    }

    TEST(SubtractEquals)
    {
        TimeSpan t = TimeSpan::fromMicroseconds(10);
        t -= TimeSpan::fromMicroseconds(5);
        CHECK_EQUAL(5, t.microseconds());
    }

    TEST(Multiply)
    {
        TimeSpan t = TimeSpan::fromMicroseconds(10) * 2.5;
        CHECK_EQUAL(25, t.microseconds());
    }

    TEST(MultiplyEquals)
    {
        TimeSpan t = TimeSpan::fromMicroseconds(10);
        t *= 2.5;
        CHECK_EQUAL(25, t.microseconds());
    }

    TEST(Divide)
    {
        TimeSpan t = TimeSpan::fromMicroseconds(10) / 2.0;
        CHECK_EQUAL(5, t.microseconds());
    }

    TEST(DivideEquals)
    {
        TimeSpan t = TimeSpan::fromMicroseconds(10);
        t /= 2.0;
        CHECK_EQUAL(5, t.microseconds());
    }

    TEST(Negate)
    {
        TimeSpan t = -TimeSpan::fromMicroseconds(10);
        CHECK_EQUAL(-10, t.microseconds());
    }
}