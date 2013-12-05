#pragma once

namespace hect
{

///
/// Provides access for writing values to a component serialization medium.
class ComponentWriter
{
public:

    ///
    /// Writes a number value.
    ///
    /// \param name The name of the value.
    /// \param value The value.
    virtual void writeNumber(const char* name, double value) = 0;

    ///
    /// Writes a string value.
    ///
    /// \param name The name of the value.
    /// \param value The value.
    virtual void writeString(const char* name, const std::string& value) = 0;

    ///
    /// Writes a 2-dimensional vector value.
    ///
    /// \param name The name of the value.
    /// \param value The value.
    virtual void writeVector2(const char* name, const Vector2<>& value) = 0;

    ///
    /// Writes a 3-dimensional vector value.
    ///
    /// \param name The name of the value.
    /// \param value The value
    virtual void writeVector3(const char* name, const Vector3<>& value) = 0;

    ///
    /// Writes a 4-dimensional vector value.
    ///
    /// \param name The name of the value.
    /// \param value The value
    virtual void writeVector4(const char* name, const Vector4<>& value) = 0;

    ///
    /// Writes a quaternion value.
    ///
    /// \param name The name of the value.
    /// \param value The value
    virtual void writeQuaternion(const char* name, const Quaternion<>& value) = 0;
};

///
/// Implementation of ComponentWriter for writing to data values.
class DataValueComponentWriter :
    public ComponentWriter
{
public:

    ///
    /// \copydoc ComponentWriter::writeNumber()
    void writeNumber(const char* name, double value);

    ///
    /// \copydoc ComponentWriter::writeString()
    void writeString(const char* name, const std::string& value);

    ///
    /// \copydoc ComponentWriter::writeVector2()
    void writeVector2(const char* name, const Vector2<>& value);

    ///
    /// \copydoc ComponentWriter::writeVector3()
    void writeVector3(const char* name, const Vector3<>& value);

    ///
    /// \copydoc ComponentWriter::writeVector4()
    void writeVector4(const char* name, const Vector4<>& value);

    ///
    /// \copydoc ComponentWriter::writeQuaternion()
    void writeQuaternion(const char* name, const Quaternion<>& value);

    ///
    /// Returns the data value written thus far.
    DataValue dataValue() const;

private:
    DataValue::Object _members;
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
    /// \copydoc ComponentWriter::writeNumber()
    void writeNumber(const char* name, double value);

    ///
    /// \copydoc ComponentWriter::writeString()
    void writeString(const char* name, const std::string& value);

    ///
    /// \copydoc ComponentWriter::writeVector2()
    void writeVector2(const char* name, const Vector2<>& value);

    ///
    /// \copydoc ComponentWriter::writeVector3()
    void writeVector3(const char* name, const Vector3<>& value);

    ///
    /// \copydoc ComponentWriter::writeVector4()
    void writeVector4(const char* name, const Vector4<>& value);

    ///
    /// \copydoc ComponentWriter::writeQuaternion()
    void writeQuaternion(const char* name, const Quaternion<>& value);

private:
    WriteStream* _stream;
};

}