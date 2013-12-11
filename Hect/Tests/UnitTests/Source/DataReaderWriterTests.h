SUITE(DataReaderWriter)
{
    void writeSimple(DataWriter& writer)
    {
        writer.writeString("String", "Testing 1 2 3");
        writer.writeDouble("Double", 5);
        writer.writeVector2("Vector2", Vector2<>(1, 2));
        writer.writeVector3("Vector3", Vector3<>(1, 2, 3));
        writer.writeVector4("Vector4", Vector4<>(1, 2, 3, 4));
    }

    void readSimple(DataReader& reader)
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

    TEST(SimpleDataValue)
    {
        DataValue dataValue;
        {
            DataValueWriter writer;
            writeSimple(writer);
            dataValue = writer.rootDataValue();
        }

        {
            DataValueReader reader(dataValue);
            readSimple(reader);
        }
    }

    TEST(SimpleBinary)
    {
        std::vector<uint8_t> data;
        {
            MemoryWriteStream stream(data);
            BinaryDataWriter writer(stream);
            writeSimple(writer);
        }

        {
            MemoryReadStream stream(data);
            BinaryDataReader reader(stream);
            readSimple(reader);
        }
    }

    void writeObject(DataWriter& writer)
    {
        writer.writeString("String", "Testing 1 2 3");
        writer.writeDouble("Double", 5);
        writer.beginObject("Object");
        writer.writeVector2("Vector2", Vector2<>(1, 2));
        writer.writeVector3("Vector3", Vector3<>(1, 2, 3));
        writer.writeVector4("Vector4", Vector4<>(1, 2, 3, 4));
        writer.endObject();
    }

    void readObject(DataReader& reader)
    {
        CHECK(reader.hasMember("String"));
        CHECK_EQUAL("Testing 1 2 3", reader.readString("String"));

        CHECK(reader.hasMember("Double"));
        CHECK_EQUAL(5, reader.readDouble("Double"));
        
        CHECK(reader.beginObject("Object"));

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

    TEST(ObjectDataValue)
    {
        DataValue dataValue;
        {
            DataValueWriter writer;
            writeObject(writer);
            dataValue = writer.rootDataValue();
        }

        {
            DataValueReader reader(dataValue);
            readObject(reader);
        }
    }

    TEST(ObjectBinary)
    {
        std::vector<uint8_t> data;
        {
            MemoryWriteStream stream(data);
            BinaryDataWriter writer(stream);
            writeObject(writer);
        }

        {
            MemoryReadStream stream(data);
            BinaryDataReader reader(stream);
            readObject(reader);
        }
    }

    void writeArray(DataWriter& writer)
    {
        writer.writeString("String", "Testing 1 2 3");
        writer.writeDouble("Double", 5);
        writer.beginArray("Array");
        writer.writeVector2(Vector2<>(1, 2));
        writer.writeVector3(Vector3<>(1, 2, 3));
        writer.writeVector4(Vector4<>(1, 2, 3, 4));
        writer.endArray();
    }

    void readArray(DataReader& reader)
    {
        CHECK(reader.hasMember("String"));
        CHECK_EQUAL("Testing 1 2 3", reader.readString("String"));

        CHECK(reader.hasMember("Double"));
        CHECK_EQUAL(5, reader.readDouble("Double"));
        
        CHECK(reader.beginArray("Array"));

        CHECK(!reader.endArray());

        Vector2<> vector2 = reader.readVector2();
        CHECK_EQUAL(1, vector2.x);
        CHECK_EQUAL(2, vector2.y);

        CHECK(!reader.endArray());

        Vector3<> vector3 = reader.readVector3();
        CHECK_EQUAL(1, vector3.x);
        CHECK_EQUAL(2, vector3.y);
        CHECK_EQUAL(3, vector3.z);

        CHECK(!reader.endArray());
        
        Vector4<> vector4 = reader.readVector4();
        CHECK_EQUAL(1, vector4.x);
        CHECK_EQUAL(2, vector4.y);
        CHECK_EQUAL(3, vector4.z);
        CHECK_EQUAL(4, vector4.w);

        CHECK(reader.endArray());
    }

    TEST(ArrayDataValue)
    {
        DataValue dataValue;
        {
            DataValueWriter writer;
            writeArray(writer);
            dataValue = writer.rootDataValue();
        }

        {
            DataValueReader reader(dataValue);
            readArray(reader);
        }
    }

    TEST(ArrayBinary)
    {
        std::vector<uint8_t> data;
        {
            MemoryWriteStream stream(data);
            BinaryDataWriter writer(stream);
            writeArray(writer);
        }

        {
            MemoryReadStream stream(data);
            BinaryDataReader reader(stream);
            readArray(reader);
        }
    }

    void writeArrayWithUnnamedObject(DataWriter& writer)
    {
        writer.beginArray("Array");
        writer.beginObject();
        writer.writeString("String", "Testing 1 2 3");
        writer.endObject();
        writer.endArray();
    }

    void readArrayWithUnnamedObject(DataReader& reader)
    {
        CHECK(reader.beginArray("Array"));
        
        CHECK(!reader.endArray());

        CHECK(reader.beginObject());
        CHECK_EQUAL("Testing 1 2 3", reader.readString("String"));
        reader.endObject();

        CHECK(reader.endArray());
    }

    TEST(ArrayWithUnnamedObjectDataValue)
    {
        DataValue dataValue;
        {
            DataValueWriter writer;
            writeArrayWithUnnamedObject(writer);
            dataValue = writer.rootDataValue();
        }

        {
            DataValueReader reader(dataValue);
            readArrayWithUnnamedObject(reader);
        }
    }

    TEST(ArrayWithUnnamedObjectBinary)
    {
        std::vector<uint8_t> data;
        {
            MemoryWriteStream stream(data);
            BinaryDataWriter writer(stream);
            writeArrayWithUnnamedObject(writer);
        }

        {
            MemoryReadStream stream(data);
            BinaryDataReader reader(stream);
            readArrayWithUnnamedObject(reader);
        }
    }
}