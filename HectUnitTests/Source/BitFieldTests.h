SUITE(BitField)
{
    TEST(ConstructAndCast)
    {
        BitField<int32_t> bitField;
        CHECK_EQUAL(0, (int32_t)bitField);
    }

    TEST(SetAndGet)
    {
        BitField<int32_t> bitField;

        bitField.set(0, true);
        for (size_t i = 1; i < 32; ++i)
        {
            if (i == 0)
            {
                CHECK(bitField.get(0));
            }
            else
            {
                CHECK(!bitField.get(i));
            }
        }

        bitField.set(6, true);
        for (size_t i = 1; i < 32; ++i)
        {
            if (i == 6 || i == 0)
            {
                CHECK(bitField.get(0));
            }
            else
            {
                CHECK(!bitField.get(i));
            }
        }
    }

    TEST(Contains)
    {
        BitField<int32_t> bitField;
        bitField.set(1, true);
        bitField.set(2, true);
        bitField.set(3, true);
        bitField.set(5, true);
        bitField.set(8, true);

        CHECK(bitField.contains(bitField));
        CHECK(!bitField.contains(~(int32_t)bitField));
        CHECK(BitField<int32_t>(0xffffffff).contains(bitField));
    }

    TEST(Clear)
    {
        BitField<int32_t> bitField;
        bitField.set(1, true);
        bitField.set(2, true);
        bitField.set(3, true);
        bitField.set(5, true);
        bitField.set(8, true);
        bitField.clear();
        for (size_t i = 1; i < 32; ++i)
        {
            CHECK(!bitField.get(i));
        }
    }
}