#pragma once

namespace hect
{

///
/// An interface for reading hierarchical data.
class DataReader
{
public:
    virtual ~DataReader() { }

    ///
    /// Begins an unnamed object.
    ///
    /// \throws Error If the current value is not an array.
    virtual void beginObject() = 0;

    ///
    /// Begins a named object.
    ///
    /// \returns Whether an object with the given name was found as a member
    /// of the current value.
    ///
    /// \param name The name of the object.
    ///
    /// \throws Error If the current value is not an object.
    virtual bool beginObject(const char* name) = 0;

    ///
    /// Ends the current object.
    ///
    /// \throws Error If the current value is not an object.
    virtual void endObject() = 0;

    ///
    /// Begins a named array.
    ///
    /// \param name The name of the array.
    ///
    /// \returns Whether an array with the given name was found as a member
    /// of the current value.
    ///
    /// \throws Error If the current value is not an object.
    virtual bool beginArray(const char* name) = 0;

    ///
    /// Ends the current array.
    ///
    /// \returns True if the end of the array was reached; false otherwise.
    ///
    /// \throws Error If the current value is not an array.
    virtual bool endArray() = 0;

    ///
    /// Returns whether or not there is a member of the current value of a
    /// given name.
    ///
    /// \throws Error If the current value is not an object.
    virtual bool hasMember(const char* name) = 0;

    ///
    /// Reads an unnamed double.
    ///
    /// \returns The read value.
    ///
    /// \throw Error If the current value is not an array.
    virtual double readDouble() = 0;

    ///
    /// Reads a named double.
    ///
    /// \param name The member name of the value to read.
    ///
    /// \returns The read value.
    ///
    /// \throw Error If the current value is not an object.
    virtual double readDouble(const char* name) = 0;

    ///
    /// Reads an unnamed string.
    ///
    /// \returns The read value.
    ///
    /// \throw Error If the current value is not an array.
    virtual std::string readString() = 0;

    ///
    /// Reads a named string.
    ///
    /// \param name The member name of the value to read.
    ///
    /// \returns The read value.
    ///
    /// \throw Error If the current value is not an object.
    virtual std::string readString(const char* name) = 0;

    ///
    /// Reads an unnamed 2-dimensional vector.
    ///
    /// \returns The read value.
    ///
    /// \throw Error If the current value is not an array.
    virtual Vector2<> readVector2() = 0;

    ///
    /// Reads a named 2-dimensional vector.
    ///
    /// \param name The member name of the value to read.
    ///
    /// \returns The read value.
    ///
    /// \throw Error If the current value is not an object
    virtual Vector2<> readVector2(const char* name) = 0;

    ///
    /// Reads an unnamed 3-dimensional vector.
    ///
    /// \returns The read value.
    ///
    /// \throw Error If the current value is not an array.
    virtual Vector3<> readVector3() = 0;

    ///
    /// Reads a named 3-dimensional vector.
    ///
    /// \param name The member name of the value to read.
    ///
    /// \returns The read value.
    ///
    /// \throw Error If the current value is not an object
    virtual Vector3<> readVector3(const char* name) = 0;

    ///
    /// Reads an unnamed 4-dimensional vector.
    ///
    /// \returns The read value.
    ///
    /// \throw Error If the current value is not an array.
    virtual Vector4<> readVector4() = 0;

    ///
    /// Reads a named 4-dimensional vector.
    ///
    /// \param name The member name of the value to read.
    ///
    /// \returns The read value.
    ///
    /// \throw Error If the current value is not an object
    virtual Vector4<> readVector4(const char* name) = 0;
};

///
/// An implementation of DataReader for reading directly from a data value.
class DataValueReader :
    public DataReader
{
public:

    ///
    /// Constructs the data value reader given the data value to read.
    ///
    /// \param dataValue The data value to read.
    DataValueReader(const DataValue& dataValue);

    void beginObject();
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

///
/// An implementation of DataReader for reading from a binary stream.
///
/// \remarks This implementation does not throw the exceptions described
/// in the DataReader documentation for performance reasons.
class BinaryDataReader :
    public DataReader
{
public:

    ///
    /// Constructs a binary data reader given the stream to read from.
    ///
    /// \param stream The stream to read from.
    BinaryDataReader(ReadStream& stream);

    void beginObject();
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