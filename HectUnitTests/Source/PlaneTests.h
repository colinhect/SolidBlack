SUITE(Plane)
{
    template <typename T>
    void testFromPoints()
    {
        Plane<T> p = Plane<T>::fromPoints(Vector3<T>(-1, 0, -1), Vector3<T>(0, 0, 0), Vector3<T>(1, 0, -1));

        CHECK_EQUAL(0, p.position().x);
        CHECK_EQUAL(0, p.position().y);
        CHECK_EQUAL(0, p.position().z);
        CHECK_EQUAL(0, p.normal().x);
        CHECK_EQUAL(1, p.normal().y);
        CHECK_EQUAL(0, p.normal().z);
        CHECK_EQUAL(0, p.distance());
    }

    TEST(FromPoints)
    {
        testFromPoints<float>();
        testFromPoints<double>();
    }
}