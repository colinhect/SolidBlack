void testWriteAndReadFile(std::function<void(WriteStream*)> writer, std::function<void(ReadStream*)> reader)
{
    Storage storage;
    Path workingDirectory = storage.workingDirectory();

    storage.addDataSource(workingDirectory);
    storage.setWriteDirectory(workingDirectory);

    Path path("File.txt");

    CHECK(!storage.exists(path));
    {
        FileWriteStream stream = storage.openFileForWrite(path);
        writer(&stream);
    }
    CHECK(storage.exists(path));
    {
        FileReadStream stream = storage.openFileForRead(path);
        reader(&stream);
    }
    storage.remove(path);
    CHECK(!storage.exists(path));
}

SUITE(Storage)
{
    TEST(Constructor)
    {
        Storage storage;
    }

    TEST(CreateAndRemoveDirectories)
    {
        Storage storage;
        Path workingDirectory = storage.workingDirectory();

        storage.addDataSource(workingDirectory);
        storage.setWriteDirectory(workingDirectory);

        Path path("Directory");

        CHECK(!storage.exists(path));
        storage.createDirectory(path);
        CHECK(storage.exists(path));
        storage.remove(path);
        CHECK(!storage.exists(path));
    }

    TEST(OpenNonExistingFileForWrite)
    {
        Storage storage;
        Path workingDirectory = storage.workingDirectory();

        storage.addDataSource(workingDirectory);
        storage.setWriteDirectory(workingDirectory);

        Path path("File.txt");

        CHECK(!storage.exists(path));
        {
            FileWriteStream stream = storage.openFileForWrite(path);
        }
        CHECK(storage.exists(path));
        storage.remove(path);
        CHECK(!storage.exists(path));
    }

    TEST(OpenExistingFileForWrite)
    {
        Storage storage;
        Path workingDirectory = storage.workingDirectory();

        storage.addDataSource(workingDirectory);
        storage.setWriteDirectory(workingDirectory);

        Path path("File.txt");

        CHECK(!storage.exists(path));
        {
            FileWriteStream stream = storage.openFileForWrite(path);
        }
        CHECK(storage.exists(path));
        {
            FileWriteStream stream = storage.openFileForWrite(path);
        }
        CHECK(storage.exists(path));
        storage.remove(path);
        CHECK(!storage.exists(path));
    }

    TEST(OpenExistingFileForRead)
    {
        Storage storage;
        Path workingDirectory = storage.workingDirectory();

        storage.addDataSource(workingDirectory);
        storage.setWriteDirectory(workingDirectory);

        Path path("File.txt");

        CHECK(!storage.exists(path));
        {
            FileWriteStream stream = storage.openFileForWrite(path);
        }
        CHECK(storage.exists(path));
        {
            FileReadStream stream = storage.openFileForRead(path);
        }

        storage.remove(path);
        CHECK(!storage.exists(path));
    }

    TEST(OpenNonExistingFileForRead)
    {
        Storage storage;
        Path workingDirectory = storage.workingDirectory();

        storage.addDataSource(workingDirectory);

        Path path("File.txt");

        bool errorOccurred = false;

        try
        {
            FileReadStream stream = storage.openFileForRead(path);
        }
        catch (Error&)
        {
            errorOccurred = true;
        }

        CHECK(errorOccurred);
    }

    TEST(FileWriteAndReadPastEndOfStream)
    {
        testWriteAndReadFile([] (WriteStream* stream)
        {
            stream->writeString("Testing");
        }, [] (ReadStream* stream)
        {
            bool errorOccurred = false;

            try
            {
                uint8_t data[16];
                stream->readBytes(data, 16);
            }
            catch (Error&)
            {
                errorOccurred = true;
            }

            CHECK(errorOccurred);
        });
    }

    TEST(WriteAndReadString)
    {
        testWriteAndReadFile([] (WriteStream* stream)
        {
            stream->writeString("Testing");
        }, [] (ReadStream* stream)
        {
            std::string string = stream->readString();
            CHECK_EQUAL("Testing", string);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadByte)
    {
        testWriteAndReadFile([] (WriteStream* stream)
        {
            stream->writeByte(123);
        }, [] (ReadStream* stream)
        {
            int8_t value = stream->readByte();
            CHECK_EQUAL(123, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadUnsignedByte)
    {
        testWriteAndReadFile([] (WriteStream* stream)
        {
            stream->writeUnsignedByte(123);
        }, [] (ReadStream* stream)
        {
            uint8_t value = stream->readUnsignedByte();
            CHECK_EQUAL(123, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadShort)
    {
        testWriteAndReadFile([] (WriteStream* stream)
        {
            stream->writeShort(123);
        }, [] (ReadStream* stream)
        {
            int16_t value = stream->readShort();
            CHECK_EQUAL(123, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadUnsignedShort)
    {
        testWriteAndReadFile([] (WriteStream* stream)
        {
            stream->writeUnsignedShort(123);
        }, [] (ReadStream* stream)
        {
            int16_t value = stream->readUnsignedShort();
            CHECK_EQUAL(123, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadInt)
    {
        testWriteAndReadFile([] (WriteStream* stream)
        {
            stream->writeInt(123);
        }, [] (ReadStream* stream)
        {
            int32_t value = stream->readInt();
            CHECK_EQUAL(123, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadUnsignedInt)
    {
        testWriteAndReadFile([] (WriteStream* stream)
        {
            stream->writeUnsignedInt(123);
        }, [] (ReadStream* stream)
        {
            uint32_t value = stream->readUnsignedInt();
            CHECK_EQUAL(123, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadLong)
    {
        testWriteAndReadFile([] (WriteStream* stream)
        {
            stream->writeLong(123456789);
        }, [] (ReadStream* stream)
        {
            int64_t value = stream->readLong();
            CHECK_EQUAL(123456789, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadUnsignedLong)
    {
        testWriteAndReadFile([] (WriteStream* stream)
        {
            stream->writeUnsignedLong(123456789);
        }, [] (ReadStream* stream)
        {
            uint64_t value = stream->readUnsignedLong();
            CHECK_EQUAL(123456789, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadFloat)
    {
        testWriteAndReadFile([] (WriteStream* stream)
        {
            stream->writeFloat((float)pi);
        }, [] (ReadStream* stream)
        {
            float value = stream->readFloat();
            CHECK_CLOSE(pi, value, epsilon);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadDouble)
    {
        testWriteAndReadFile([] (WriteStream* stream)
        {
            stream->writeDouble(pi);
        }, [] (ReadStream* stream)
        {
            double value = stream->readDouble();
            CHECK_CLOSE(pi, value, epsilon);
            CHECK(stream->endOfStream());
        });
    }
}