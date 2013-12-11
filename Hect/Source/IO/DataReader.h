#pragma once

namespace hect
{

///
/// An interface for reading hierarchical data.
class DataReader
{
public:
    virtual ~DataReader() { }
    
    virtual bool beginObject() = 0;
    virtual bool beginObject(const char* name) = 0;
    virtual void endObject() = 0;
    virtual bool beginArray(const char* name) = 0;
    virtual bool endArray() = 0;
    virtual bool hasMember(const char* name) = 0;
    virtual double readDouble() = 0;
    virtual double readDouble(const char* name) = 0;
    virtual std::string readString() = 0;
    virtual std::string readString(const char* name) = 0;
    virtual Vector2<> readVector2() = 0;
    virtual Vector2<> readVector2(const char* name) = 0;
    virtual Vector3<> readVector3() = 0;
    virtual Vector3<> readVector3(const char* name) = 0;
    virtual Vector4<> readVector4() = 0;
    virtual Vector4<> readVector4(const char* name) = 0;
};

class DataValueReader :
    public DataReader
{
public:
    DataValueReader(const DataValue& dataValue);
    
    bool beginObject();
    bool beginObject(const char* name);
    void endObject();
    bool beginArray(const char* name);
    bool endArray();
    bool hasMember(const char* name);
    double readDouble();
    double readDouble(const char* name);
    std::string readString();
    std::string readString(const char* name);
    Vector2<> readVector2();
    Vector2<> readVector2(const char* name);
    Vector3<> readVector3();
    Vector3<> readVector3(const char* name);
    Vector4<> readVector4();
    Vector4<> readVector4(const char* name);

private:
    const DataValue& _read();
    const DataValue& _read(const char* name);

    size_t _elementIndex;
    std::stack<DataValue> _valueStack;
};

class BinaryDataReader :
    public DataReader
{
public:
    BinaryDataReader(ReadStream& stream);
    
    bool beginObject();
    bool beginObject(const char* name);
    void endObject();
    bool beginArray(const char* name);
    bool endArray();
    bool hasMember(const char* name);
    double readDouble();
    double readDouble(const char* name);
    std::string readString();
    std::string readString(const char* name);
    Vector2<> readVector2();
    Vector2<> readVector2(const char* name);
    Vector3<> readVector3();
    Vector3<> readVector3(const char* name);
    Vector4<> readVector4();
    Vector4<> readVector4(const char* name);

private:
    unsigned _elementIndex;
    unsigned _elementCount;
    ReadStream* _stream;
};

}