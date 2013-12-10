SUITE(DataReaderWriter)
{
    void writeFlatObject(DataWriter& writer)
    {
        writer.writeString("String", "Testing 1 2 3");
        writer.writeDouble("Double", 5);
        writer.writeVector2("Vector2", Vector2<>(1, 2));
        writer.writeVector3("Vector3", Vector3<>(1, 2, 3));
        writer.writeVector4("Vector4", Vector4<>(1, 2, 3, 4));
    }

    void readFlatObject(DataReader& reader)
    {
        CHECK(reader.hasMember("String"));
        CHECK_EQUAL("Testing 1 2 3", reader.readString("String"));

        CHECK(reader.hasMember("Double"));
        CHECK_EQUAL(5, reader.readDouble("Double"));
        
        CHECK(reader.hasMember("Vector2"));
        Vector2<> vector2 = reader.readVector2("Vector2");
        CHECK_EQUAL(1, vector2.x);
        CHECK_EQUAL(2, vector2.y);
        
        CHECK(reader.hasMember("Vector3"));
        Vector3<> vector3 = reader.readVector3("Vector3");
        CHECK_EQUAL(1, vector3.x);
        CHECK_EQUAL(2, vector3.y);
        CHECK_EQUAL(3, vector3.z);
        
        CHECK(reader.hasMember("Vector4"));
        Vector4<> vector4 = reader.readVector4("Vector4");
        CHECK_EQUAL(1, vector4.x);
        CHECK_EQUAL(2, vector4.y);
        CHECK_EQUAL(3, vector4.z);
        CHECK_EQUAL(4, vector4.w);
    }

    TEST(FlatObjectDataValue)
    {
        DataValue dataValue;
        {
            DataValueWriter writer;
            writeFlatObject(writer);
            dataValue = writer.rootDataValue();
        }

        {
            DataValueReader reader(dataValue);
            readFlatObject(reader);
        }
    }

    TEST(FlatObjectBinary)
    {
        std::vector<uint8_t> data;
        {
            MemoryWriteStream stream(data);
            BinaryDataWriter writer(stream);
            writeFlatObject(writer);
        }

        {
            MemoryReadStream stream(data);
            BinaryDataReader reader(stream);
            readFlatObject(reader);
        }
    }

    void writeNestedObject(DataWriter& writer)
    {
        writer.writeString("String", "Testing 1 2 3");
        writer.writeDouble("Double", 5);
        writer.beginObject("NestedObject");
        writer.writeVector2("Vector2", Vector2<>(1, 2));
        writer.writeVector3("Vector3", Vector3<>(1, 2, 3));
        writer.writeVector4("Vector4", Vector4<>(1, 2, 3, 4));
        writer.endObject();
    }

    void readNestedObject(DataReader& reader)
    {
        CHECK(reader.hasMember("String"));
        CHECK_EQUAL("Testing 1 2 3", reader.readString("String"));

        CHECK(reader.hasMember("Double"));
        CHECK_EQUAL(5, reader.readDouble("Double"));
        
        CHECK(reader.beginObject("NestedObject"));

        CHECK(reader.hasMember("Vector2"));
        Vector2<> vector2 = reader.readVector2("Vector2");
        CHECK_EQUAL(1, vector2.x);
        CHECK_EQUAL(2, vector2.y);
        
        CHECK(reader.hasMember("Vector3"));
        Vector3<> vector3 = reader.readVector3("Vector3");
        CHECK_EQUAL(1, vector3.x);
        CHECK_EQUAL(2, vector3.y);
        CHECK_EQUAL(3, vector3.z);
        
        CHECK(reader.hasMember("Vector4"));
        Vector4<> vector4 = reader.readVector4("Vector4");
        CHECK_EQUAL(1, vector4.x);
        CHECK_EQUAL(2, vector4.y);
        CHECK_EQUAL(3, vector4.z);
        CHECK_EQUAL(4, vector4.w);

        reader.endObject();
    }

    TEST(NestedObjectDataValue)
    {
        DataValue dataValue;
        {
            DataValueWriter writer;
            writeNestedObject(writer);
            dataValue = writer.rootDataValue();
        }

        {
            DataValueReader reader(dataValue);
            readNestedObject(reader);
        }
    }

    TEST(NestedObjectBinary)
    {
        std::vector<uint8_t> data;
        {
            MemoryWriteStream stream(data);
            BinaryDataWriter writer(stream);
            writeNestedObject(writer);
        }

        {
            MemoryReadStream stream(data);
            BinaryDataReader reader(stream);
            readNestedObject(reader);
        }
    }
}