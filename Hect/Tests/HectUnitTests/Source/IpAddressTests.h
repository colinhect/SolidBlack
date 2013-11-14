SUITE(IpAddress)
{
    TEST(LocalAddress)
    {
        IpAddress address = IpAddress::localAddress();
        CHECK(address.toString() != "0.0.0.0");

        IpAddress addressFromString(address.toString());
        CHECK_EQUAL(address.toString(), addressFromString.toString());
    }
}