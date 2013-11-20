SUITE(Frustum)
{
    template <typename T>
    void testOutsideBehind()
    {
        Frustum<T> frustum(
            Vector3<T>(0, 0, 0),
            Vector3<T>(0, 0, -1),
            Vector3<T>(0, 1, 0),
            Angle<T>::fromDegrees(90),
            1,
            (T)0.1,
            100);

        AxisAlignedBox<T> box(Vector3<T>(-1, -1, 10), Vector3<T>(1, 1, 11));

        CHECK(FrustumTestResult::Outside == frustum.testAxisAlignedBox(box));
    }

    TEST(OutsideBehind)
    {
        testOutsideBehind<float>();
        testOutsideBehind<double>();
    }

    template <typename T>
    void testOutsideLeft()
    {
        Frustum<T> frustum(
            Vector3<T>(0, 0, 0),
            Vector3<T>(0, 0, -1),
            Vector3<T>(0, 1, 0),
            Angle<T>::fromDegrees(90),
            1,
            (T)0.1,
            100);

        AxisAlignedBox<T> box(Vector3<T>(-100, -1, -11), Vector3<T>(-101, 1, -10));

        CHECK(FrustumTestResult::Outside == frustum.testAxisAlignedBox(box));
    }

    TEST(OutsideLeft)
    {
        testOutsideLeft<float>();
        testOutsideLeft<double>();
    }

    template <typename T>
    void testInside()
    {
        Frustum<T> frustum(
            Vector3<T>(0, 0, 0),
            Vector3<T>(0, 0, -1),
            Vector3<T>(0, 1, 0),
            Angle<T>::fromDegrees(90),
            1,
            (T)0.1,
            100);

        AxisAlignedBox<T> box(Vector3<T>(-1, -1, -50), Vector3<T>(1, 1, -51));

        CHECK(FrustumTestResult::Inside == frustum.testAxisAlignedBox(box));
    }

    TEST(Inside)
    {
        testInside<float>();
        testInside<double>();
    }

    template <typename T>
    void testIntersect()
    {
        Frustum<T> frustum(
            Vector3<T>(0, 0, 0),
            Vector3<T>(0, 0, -1),
            Vector3<T>(0, 1, 0),
            Angle<T>::fromDegrees(90),
            1,
            (T)0.1,
            100);

        AxisAlignedBox<T> box(Vector3<T>(-1, -1, -200), Vector3<T>(1, 1, -51));

        CHECK(FrustumTestResult::Intersect == frustum.testAxisAlignedBox(box));
    }

    TEST(Intersect)
    {
        testIntersect<float>();
        testIntersect<double>();
    }
}