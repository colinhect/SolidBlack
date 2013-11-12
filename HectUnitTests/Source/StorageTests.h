void testWriteAndRead(std::function<void(WriteStream*)> writer, std::function<void(ReadStream*)> reader)
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
        testWriteAndRead([] (WriteStream* stream)
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
        testWriteAndRead([] (WriteStream* stream)
        {
            stream->writeString("Testing");
        }, [] (ReadStream* stream)
        {
            std::string string = stream->readString();
            CHECK_EQUAL("Testing", string);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadSigned8)
    {
        testWriteAndRead([] (WriteStream* stream)
        {
            stream->writeSigned8(123);
        }, [] (ReadStream* stream)
        {
            int8_t value = stream->readSigned8();
            CHECK_EQUAL(123, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadUnsigned8)
    {
        testWriteAndRead([] (WriteStream* stream)
        {
            stream->writeUnsigned8(123);
        }, [] (ReadStream* stream)
        {
            uint8_t value = stream->readUnsigned8();
            CHECK_EQUAL(123, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadSigned16)
    {
        testWriteAndRead([] (WriteStream* stream)
        {
            stream->writeSigned16(123);
        }, [] (ReadStream* stream)
        {
            int16_t value = stream->readSigned16();
            CHECK_EQUAL(123, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadUnsigned16)
    {
        testWriteAndRead([] (WriteStream* stream)
        {
            stream->writeUnsigned16(123);
        }, [] (ReadStream* stream)
        {
            int16_t value = stream->readUnsigned16();
            CHECK_EQUAL(123, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadSigned32)
    {
        testWriteAndRead([] (WriteStream* stream)
        {
            stream->writeSigned32(123);
        }, [] (ReadStream* stream)
        {
            int32_t value = stream->readSigned32();
            CHECK_EQUAL(123, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadUnsigned32)
    {
        testWriteAndRead([] (WriteStream* stream)
        {
            stream->writeUnsigned32(123);
        }, [] (ReadStream* stream)
        {
            uint32_t value = stream->readUnsigned32();
            CHECK_EQUAL(123, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadSigned64)
    {
        testWriteAndRead([] (WriteStream* stream)
        {
            stream->writeSigned64(123456789);
        }, [] (ReadStream* stream)
        {
            int64_t value = stream->readSigned64();
            CHECK_EQUAL(123456789, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadUnsigned64)
    {
        testWriteAndRead([] (WriteStream* stream)
        {
            stream->writeUnsigned64(123456789);
        }, [] (ReadStream* stream)
        {
            uint64_t value = stream->readUnsigned64();
            CHECK_EQUAL(123456789, value);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadFloat32)
    {
        testWriteAndRead([] (WriteStream* stream)
        {
            stream->writeFloat32((float)pi);
        }, [] (ReadStream* stream)
        {
            float value = stream->readFloat32();
            CHECK_CLOSE(pi, value, epsilon);
            CHECK(stream->endOfStream());
        });
    }

    TEST(WriteAndReadFloat64)
    {
        testWriteAndRead([] (WriteStream* stream)
        {
            stream->writeFloat64(pi);
        }, [] (ReadStream* stream)
        {
            double value = stream->readFloat64();
            CHECK_CLOSE(pi, value, epsilon);
            CHECK(stream->endOfStream());
        });
    }
}