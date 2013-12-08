#pragma once

namespace hect
{

///
/// Provides access for reading values from a component serialization medium.
class ComponentReader
{
public:

    virtual bool beginObject(const char* name) = 0;
    virtual void endObject() = 0;

    ///
    /// Returns whether there is a value with a given name.
    ///
    /// \param name The name of the member in question.
    ///
    /// \returns The read value.
    virtual bool hasMember(const char* name) = 0;

    ///
    /// Reads a value as a number.
    ///
    /// \param name The name of the member.
    ///
    /// \returns The read value.
    virtual double readMemberDouble(const char* name) = 0;

    ///
    /// Reads a value as a string.
    ///
    /// \param name The name of the member.
    ///
    /// \returns The read value.
    virtual std::string readMemberString(const char* name) = 0;

    ///
    /// Reads a value as a 2-dimensional vector.
    ///
    /// \param name The name of the member.
    ///
    /// \returns The read value.
    virtual Vector2<> readMemberVector2(const char* name) = 0;

    ///
    /// Reads a value as a 3-dimensional vector.
    ///
    /// \param name The name of the member.
    ///
    /// \returns The read value.
    virtual Vector3<> readMemberVector3(const char* name) = 0;

    ///
    /// Reads a value as a 4-dimensional vector.
    ///
    /// \param name The name of the member.
    ///
    /// \returns The read value.
    virtual Vector4<> readMemberVector4(const char* name) = 0;

    ///
    /// Reads a value as a quaternion.
    ///
    /// \param name The name of the member.
    ///
    /// \returns The read value.
    virtual Quaternion<> readMemberQuaternion(const char* name) = 0;
};

///
/// Implementation of ComponentReader for reading from data values.
class DataValueComponentReader :
    public ComponentReader
{
public:

    ///
    /// Constructs the reader given the data value to read from.
    ///
    /// \param dataValue The data value to read from.
    DataValueComponentReader(const DataValue& dataValue);

    ///
    /// \copydoc ComponentWriter::beginObject()
    bool beginObject(const char* name);

    ///
    /// \copydoc ComponentWriter::beginObject()
    void endObject();

    ///
    /// \copydoc ComponentReader::hasMember()
    bool hasMember(const char* name);

    ///
    /// \copydoc ComponentReader::readMemberDouble()
    double readMemberDouble(const char* name);

    ///
    /// \copydoc ComponentReader::readMemberString()
    std::string readMemberString(const char* name);

    ///
    /// \copydoc ComponentReader::readMemberVector2()
    Vector2<> readMemberVector2(const char* name);

    ///
    /// \copydoc ComponentReader::readMemberVector3()
    Vector3<> readMemberVector3(const char* name);

    ///
    /// \copydoc ComponentReader::readMemberVector4()
    Vector4<> readMemberVector4(const char* name);

    ///
    /// \copydoc ComponentReader::readMemberQuaternion()
    Quaternion<> readMemberQuaternion(const char* name);

private:
    std::stack<DataValue> _dataValueStack;
};

///
/// Implementation of ComponentReader for reading from binary streams.
class BinaryComponentReader :
    public ComponentReader
{
public:

    ///
    /// Constructs the component reader given the stream for it to read from.
    ///
    /// \param stream The stream to read from.
    BinaryComponentReader(ReadStream& stream);

    ///
    /// \copydoc ComponentWriter::beginObject()
    bool beginObject(const char* name);

    ///
    /// \copydoc ComponentWriter::beginObject()
    void endObject();

    ///
    /// \copydoc ComponentReader::hasMember()
    bool hasMember(const char* name);

    ///
    /// \copydoc ComponentReader::readMemberDouble()
    double readMemberDouble(const char* name);

    ///
    /// \copydoc ComponentReader::readMemberString()
    std::string readMemberString(const char* name);

    ///
    /// \copydoc ComponentReader::readMemberVector2()
    Vector2<> readMemberVector2(const char* name);

    ///
    /// \copydoc ComponentReader::readMemberVector3()
    Vector3<> readMemberVector3(const char* name);

    ///
    /// \copydoc ComponentReader::readMemberVector4()
    Vector4<> readMemberVector4(const char* name);

    ///
    /// \copydoc ComponentReader::readMemberQuaternion()
    Quaternion<> readMemberQuaternion(const char* name);

private:
    ReadStream* _stream;
};

}