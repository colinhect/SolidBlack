#pragma once

namespace hect
{

///
/// An interface for reading hierarchical data.
class DataReader
{
public:
    virtual ~DataReader() { }

    virtual bool beginObject(const char* memberName) = 0;
    virtual void endObject() = 0;
    virtual bool hasMember(const char* memberName) = 0;
    virtual double readDouble(const char* memberName) = 0;
    virtual std::string readString(const char* memberName) = 0;
    virtual Vector2<> readVector2(const char* memberName) = 0;
    virtual Vector3<> readVector3(const char* memberName) = 0;
    virtual Vector4<> readVector4(const char* memberName) = 0;
};

class DataValueReader :
    public DataReader
{
public:
    DataValueReader(const DataValue& dataValue);

    bool beginObject(const char* memberName);
    void endObject();
    bool hasMember(const char* memberName);
    double readDouble(const char* memberName);
    std::string readString(const char* memberName);
    Vector2<> readVector2(const char* memberName);
    Vector3<> readVector3(const char* memberName);
    Vector4<> readVector4(const char* memberName);

private:
    std::stack<DataValue> _dataValueStack;
};

class BinaryDataReader :
    public DataReader
{
public:
    BinaryDataReader(ReadStream& stream);

    ///
    /// \copydoc DataWriter::beginObject()
    bool beginObject(const char* memberName);

    ///
    /// \copydoc DataWriter::beginObject()
    void endObject();

    ///
    /// \copydoc DataReader::hasMember()
    bool hasMember(const char* memberName);

    ///
    /// \copydoc DataReader::readDouble()
    double readDouble(const char* memberName);

    ///
    /// \copydoc DataReader::readString()
    std::string readString(const char* memberName);

    ///
    /// \copydoc DataReader::readVector2()
    Vector2<> readVector2(const char* memberName);

    ///
    /// \copydoc DataReader::readVector3()
    Vector3<> readVector3(const char* memberName);

    ///
    /// \copydoc DataReader::readVector4()
    Vector4<> readVector4(const char* memberName);

private:
    ReadStream* _stream;
};

}