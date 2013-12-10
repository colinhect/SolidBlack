#pragma once

namespace hect
{
    
///
/// An interface for writing hierarchical data.
class DataWriter
{
public:
    virtual ~DataWriter() { }

    virtual void beginObject(const char* name) = 0;
    virtual void endObject() = 0;
    virtual void writeDouble(const char* name, double value) = 0;
    virtual void writeString(const char* name, const std::string& value) = 0;
    virtual void writeVector2(const char* name, const Vector2<>& value) = 0;
    virtual void writeVector3(const char* name, const Vector3<>& value) = 0;
    virtual void writeVector4(const char* name, const Vector4<>& value) = 0;
};

class DataValueWriter :
    public DataWriter
{
public:
    DataValueWriter();

    void beginObject(const char* name);
    void endObject();
    void writeDouble(const char* name, double value);
    void writeString(const char* name, const std::string& value);
    void writeVector2(const char* name, const Vector2<>& value);
    void writeVector3(const char* name, const Vector3<>& value);
    void writeVector4(const char* name, const Vector4<>& value);

    DataValue rootDataValue() const;

private:
    std::stack<std::string> _objectNameStack;
    std::stack<DataValue::Object> _objectStack;
};

class BinaryDataWriter :
    public DataWriter
{
public:
    BinaryDataWriter(WriteStream& stream);

    ///
    /// \copydoc DataWriter::beginObject()
    void beginObject(const char* name);

    ///
    /// \copydoc DataWriter::beginObject()
    void endObject();

    ///
    /// \copydoc DataWriter::writeDouble()
    void writeDouble(const char* name, double value);

    ///
    /// \copydoc DataWriter::writeString()
    void writeString(const char* name, const std::string& value);

    ///
    /// \copydoc DataWriter::writeVector2()
    void writeVector2(const char* name, const Vector2<>& value);

    ///
    /// \copydoc DataWriter::writeVector3()
    void writeVector3(const char* name, const Vector3<>& value);

    ///
    /// \copydoc DataWriter::writeVector4()
    void writeVector4(const char* name, const Vector4<>& value);

private:
    WriteStream* _stream;
};

}