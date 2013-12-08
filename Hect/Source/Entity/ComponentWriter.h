#pragma once

namespace hect
{

///
/// Provides access for writing values to a component serialization medium.
class ComponentWriter
{
public:

    virtual void beginObject(const char* name) = 0;
    virtual void endObject() = 0;

    ///
    /// Writes a number value.
    ///
    /// \param name The name of the member to write.
    /// \param value The value.
    virtual void writeMemberDouble(const char* name, double value) = 0;

    ///
    /// Writes a string value.
    ///
    /// \param name The name of the member to write.
    /// \param value The value.
    virtual void writeMemberString(const char* name, const std::string& value) = 0;

    ///
    /// Writes a 2-dimensional vector value.
    ///
    /// \param name The name of the member to write.
    /// \param value The value.
    virtual void writeMemberVector2(const char* name, const Vector2<>& value) = 0;

    ///
    /// Writes a 3-dimensional vector value.
    ///
    /// \param name The name of the member to write.
    /// \param value The value
    virtual void writeMemberVector3(const char* name, const Vector3<>& value) = 0;

    ///
    /// Writes a 4-dimensional vector value.
    ///
    /// \param name The name of the member to write.
    /// \param value The value
    virtual void writeMemberVector4(const char* name, const Vector4<>& value) = 0;

    ///
    /// Writes a quaternion value.
    ///
    /// \param name The name of the member to write.
    /// \param value The value
    virtual void writeMemberQuaternion(const char* name, const Quaternion<>& value) = 0;
};

///
/// Implementation of ComponentWriter for writing to data values.
class DataValueComponentWriter :
    public ComponentWriter
{
public:

    ///
    /// Constructs the component writer.
    DataValueComponentWriter();

    ///
    /// \copydoc ComponentWriter::beginObject()
    void beginObject(const char* name);

    ///
    /// \copydoc ComponentWriter::beginObject()
    void endObject();

    ///
    /// \copydoc ComponentWriter::writeMemberDouble()
    void writeMemberDouble(const char* name, double value);

    ///
    /// \copydoc ComponentWriter::writeMemberString()
    void writeMemberString(const char* name, const std::string& value);

    ///
    /// \copydoc ComponentWriter::writeMemberVector2()
    void writeMemberVector2(const char* name, const Vector2<>& value);

    ///
    /// \copydoc ComponentWriter::writeMemberVector3()
    void writeMemberVector3(const char* name, const Vector3<>& value);

    ///
    /// \copydoc ComponentWriter::writeMemberVector4()
    void writeMemberVector4(const char* name, const Vector4<>& value);

    ///
    /// \copydoc ComponentWriter::writeMemberQuaternion()
    void writeMemberQuaternion(const char* name, const Quaternion<>& value);

    ///
    /// Returns the data value written thus far.
    DataValue dataValue() const;

private:
    std::stack<std::string> _objectNameStack;
    std::stack<DataValue::Object> _objectStack;
};

///
/// Implementation of ComponentWriter for writing to binary streams.
class BinaryComponentWriter :
    public ComponentWriter
{
public:

    ///
    /// Constructs the component writer given the stream for it to write to.
    ///
    /// \param stream The stream to write to.
    BinaryComponentWriter(WriteStream& stream);

    ///
    /// \copydoc ComponentWriter::beginObject()
    void beginObject(const char* name);

    ///
    /// \copydoc ComponentWriter::beginObject()
    void endObject();

    ///
    /// \copydoc ComponentWriter::writeMemberDouble()
    void writeMemberDouble(const char* name, double value);

    ///
    /// \copydoc ComponentWriter::writeMemberString()
    void writeMemberString(const char* name, const std::string& value);

    ///
    /// \copydoc ComponentWriter::writeMemberVector2()
    void writeMemberVector2(const char* name, const Vector2<>& value);

    ///
    /// \copydoc ComponentWriter::writeMemberVector3()
    void writeMemberVector3(const char* name, const Vector3<>& value);

    ///
    /// \copydoc ComponentWriter::writeMemberVector4()
    void writeMemberVector4(const char* name, const Vector4<>& value);

    ///
    /// \copydoc ComponentWriter::writeMemberQuaternion()
    void writeMemberQuaternion(const char* name, const Quaternion<>& value);

private:
    WriteStream* _stream;
};

}