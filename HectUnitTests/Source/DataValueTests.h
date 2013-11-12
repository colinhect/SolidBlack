SUITE(DataValue)
{
    TEST(Null)
    {
        DataValue value;
        CHECK_EQUAL(DataValue::Null, value.type());
    }

    TEST(Bool)
    {
        DataValue value(true);
        CHECK_EQUAL(DataValue::Bool, value.type());
        CHECK(value.asBool());
    }

    TEST(Number)
    {
        DataValue value(5.0);
        CHECK_EQUAL(DataValue::Number, value.type());
        CHECK_EQUAL(5.0, value.asDouble());
    }

    TEST(String)
    {
        DataValue value("Testing");
        CHECK_EQUAL(DataValue::String, value.type());
        CHECK_EQUAL("Testing", value.asString());
    }

    TEST(Array)
    {
        auto elements = DataValue::ArrayType();
        elements.push_back(true);
        elements.push_back(5.0);
        elements.push_back("Testing");

        DataValue value(elements);
        CHECK_EQUAL(DataValue::Array, value.type());
        CHECK_EQUAL(3, value.size());

        for (unsigned i = 0; i < value.size(); ++i)
        {
            if (i == 0)
            {
                CHECK_EQUAL(DataValue::Bool, value[i].type());
                CHECK(value[i].asBool());
            }
            else if (i == 1)
            {
                CHECK_EQUAL(DataValue::Number, value[i].type());
                CHECK_EQUAL(5.0, value[i].asDouble());
            }
            else if (i == 2)
            {
                CHECK_EQUAL(DataValue::String, value[i].type());
                CHECK_EQUAL("Testing", value[i].asString());
            }
        }
    }

    TEST(Object)
    {
        auto members = DataValue::ObjectType();
        members["someBool"] = true;
        members["someNumber"] = 5.0;
        members["someString"] = "Testing";

        DataValue value(members);
        CHECK_EQUAL(DataValue::Object, value.type());
        CHECK_EQUAL(3, value.size());

        CHECK_EQUAL(DataValue::Bool, value["someBool"].type());
        CHECK(value["someBool"].asBool());
        CHECK_EQUAL(DataValue::Number, value["someNumber"].type());
        CHECK_EQUAL(5.0, value["someNumber"].asDouble());
        CHECK_EQUAL(DataValue::String, value["someString"].type());
        CHECK_EQUAL("Testing", value["someString"].asString());
    }

    TEST(MemberNames)
    {
        auto members = DataValue::ObjectType();
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
        auto elements = DataValue::ArrayType();
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
            CHECK(false);
        }
    }

    TEST(DeepNull)
    {
        DataValue value;
        CHECK(value["root"][10]["something"].isNull());
    }
}