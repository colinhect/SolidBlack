#pragma once

namespace hect
{
    
///
/// An interface for writing hierarchical data.
class DataWriter
{
public:
    virtual ~DataWriter() { }
    
    virtual void beginObject() = 0;
    virtual void beginObject(const char* name) = 0;
    virtual void endObject() = 0;

    virtual void beginArray(const char* name) = 0;
    virtual void endArray() = 0;

    virtual void writeDouble(double value) = 0;
    virtual void writeDouble(const char* name, double value) = 0;
    virtual void writeString(const std::string& value) = 0;
    virtual void writeString(const char* name, const std::string& value) = 0;
    virtual void writeVector2(const Vector2<>& value) = 0;
    virtual void writeVector2(const char* name, const Vector2<>& value) = 0;
    virtual void writeVector3(const Vector3<>& value) = 0;
    virtual void writeVector3(const char* name, const Vector3<>& value) = 0;
    virtual void writeVector4(const Vector4<>& value) = 0;
    virtual void writeVector4(const char* name, const Vector4<>& value) = 0;
};

class DataValueWriter :
    public DataWriter
{
public:
    DataValueWriter();
    
    void beginObject();
    void beginObject(const char* name);
    void endObject();
    void beginArray(const char* name);
    void endArray();
    void writeDouble(double value);
    void writeDouble(const char* name, double value);
    void writeString(const std::string& value);
    void writeString(const char* name, const std::string& value);
    void writeVector2(const Vector2<>& value);
    void writeVector2(const char* name, const Vector2<>& value);
    void writeVector3(const Vector3<>& value);
    void writeVector3(const char* name, const Vector3<>& value);
    void writeVector4(const Vector4<>& value);
    void writeVector4(const char* name, const Vector4<>& value);

    DataValue rootDataValue() const;

private:
    void _write(const DataValue& value);
    void _write(const char* name, const DataValue& value);

    std::stack<std::string> _nameStack;
    std::stack<DataValue> _valueStack;
};

class BinaryDataWriter :
    public DataWriter
{
public:
    BinaryDataWriter(WriteStream& stream);
    
    void beginObject();
    void beginObject(const char* name);
    void endObject();
    void beginArray(const char* name);
    void endArray();
    void writeDouble(double value);
    void writeDouble(const char* name, double value);
    void writeString(const std::string& value);
    void writeString(const char* name, const std::string& value);
    void writeVector2(const Vector2<>& value);
    void writeVector2(const char* name, const Vector2<>& value);
    void writeVector3(const Vector3<>& value);
    void writeVector3(const char* name, const Vector3<>& value);
    void writeVector4(const Vector4<>& value);
    void writeVector4(const char* name, const Vector4<>& value);

private:
    size_t _elementCountPosition;
    unsigned _elementCount;
    WriteStream* _stream;
};

}