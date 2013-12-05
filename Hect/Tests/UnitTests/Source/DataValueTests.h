SUITE(DataValue)
{
    TEST(Null)
    {
        DataValue value;
        CHECK(value.isNull());
    }

    TEST(Bool)
    {
        DataValue value(true);
        CHECK(value.isBool());
        CHECK(value.asBool());
    }

    TEST(Number)
    {
        DataValue value(5.0);
        CHECK(value.isNumber());
        CHECK_EQUAL(5.0, value.asDouble());
    }

    TEST(String)
    {
        DataValue value("Testing");
        CHECK(value.isString());
        CHECK_EQUAL("Testing", value.asString());
    }

    TEST(Array)
    {
        auto elements = DataValue::Array();
        elements.push_back(true);
        elements.push_back(5.0);
        elements.push_back("Testing");

        DataValue value(elements);
        CHECK(value.isArray());
        CHECK_EQUAL(3, value.size());

        for (unsigned i = 0; i < value.size(); ++i)
        {
            if (i == 0)
            {
                CHECK(value[i].isBool());
                CHECK(value[i].asBool());
            }
            else if (i == 1)
            {
                CHECK(value[i].isNumber());
                CHECK_EQUAL(5.0, value[i].asDouble());
            }
            else if (i == 2)
            {
                CHECK(value[i].isString());
                CHECK_EQUAL("Testing", value[i].asString());
            }
        }
    }

    TEST(Object)
    {
        auto members = DataValue::Object();
        members["someBool"] = true;
        members["someNumber"] = 5.0;
        members["someString"] = "Testing";

        DataValue value(members);
        CHECK(value.isObject());
        CHECK_EQUAL(3, value.size());

        CHECK(value["someBool"].isBool());
        CHECK(value["someBool"].asBool());
        CHECK(value["someNumber"].isNumber());
        CHECK_EQUAL(5.0, value["someNumber"].asDouble());
        CHECK(value["someString"].isString());
        CHECK_EQUAL("Testing", value["someString"].asString());
    }

    TEST(Vector2)
    {
        DataValue value(Vector2<>(1, 2));
        CHECK(value.isArray());

        Vector2<> v = value.asVector2();
        CHECK_EQUAL(1, v.x);
        CHECK_EQUAL(2, v.y);
    }

    TEST(Vector3)
    {
        DataValue value(Vector3<>(1, 2, 3));
        CHECK(value.isArray());

        Vector3<> v = value.asVector3();
        CHECK_EQUAL(1, v.x);
        CHECK_EQUAL(2, v.y);
        CHECK_EQUAL(3, v.z);
    }

    TEST(Vector4)
    {
        DataValue value(Vector4<>(1, 2, 3, 4));
        CHECK(value.isArray());

        Vector4<> v = value.asVector4();
        CHECK_EQUAL(1, v.x);
        CHECK_EQUAL(2, v.y);
        CHECK_EQUAL(3, v.z);
        CHECK_EQUAL(4, v.w);
    }

    TEST(MemberNames)
    {
        auto members = DataValue::Object();
        members["someBool"] = true;
        members["someNumber"] = 5.0;
        members["someString"] = "Testing";

        DataValue value(members);
        auto memberNames = value.memberNames();

        CHECK_EQUAL(3, memberNames.size());
        CHECK(std::find(memberNames.begin(), memberNames.end(), "someBool") != memberNames.end());
        CHECK(std::find(memberNames.begin(), memberNames.end(), "someNumber") != memberNames.end());
        CHECK(std::find(memberNames.begin(), memberNames.end(), "someString") != memberNames.end());
    }

    TEST(OrFromNull)
    {
        DataValue value;
        CHECK(value.or(true).asBool());
    }

    TEST(OrFromNotNull)
    {
        DataValue value(true);
        CHECK(value.or(false).asBool());
    }

    TEST(Iterate)
    {
        auto elements = DataValue::Array();
        for (int i = 0; i < 10; ++i)
        {
            elements.push_back((double)i);
        }

        DataValue value(elements);
        CHECK(value.isArray());
        CHECK_EQUAL(10, value.size());

        int i = 0;
        for (const DataValue& element : value)
        {
            CHECK(element.isNumber());
            CHECK_EQUAL(i++, element.asDouble());
        }
    }

    TEST(IterateOnNull)
    {
        DataValue value;
        for (const DataValue& element : value)
        {
            element;
            CHECK(false);
        }
    }

    TEST(DeepNull)
    {
        DataValue value;
        CHECK(value["root"][10]["something"].isNull());
    }
}