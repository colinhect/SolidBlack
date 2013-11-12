SUITE(JsonParser)
{
    TEST(Simple)
    {
        std::string json = "{ \"someBool\" : true, \"someArray\" : [ 0, 1, 2 ] }";
        DataValue value = JsonParser().parse(json);

        CHECK(value.isObject());
        CHECK_EQUAL(2, value.size());
        CHECK(value["someBool"].isBool());
        CHECK(value["someBool"].asBool());
        CHECK(value["someArray"].isArray());
        CHECK_EQUAL(3, value["someArray"].size());
        CHECK_EQUAL(0, value["someArray"][0].asInt());
        CHECK_EQUAL(1, value["someArray"][1].asInt());
        CHECK_EQUAL(2, value["someArray"][2].asInt());
    }
}