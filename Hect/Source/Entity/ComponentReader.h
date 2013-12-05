#pragma once

namespace hect
{

///
/// Provides access for reading values from a component serialization medium.
class ComponentReader
{
public:

    ///
    /// Returns whether there is a value with a given name.
    ///
    /// \param name The name of the value in question.
    ///
    /// \returns The read value.
    virtual bool hasValue(const char* name) = 0;

    ///
    /// Reads a value as a number.
    ///
    /// \param name The name of the value.
    ///
    /// \returns The read value.
    virtual double readNumber(const char* name) = 0;

    ///
    /// Reads a value as a string.
    ///
    /// \param name The name of the value.
    ///
    /// \returns The read value.
    virtual std::string readString(const char* name) = 0;

    ///
    /// Reads a value as a 2-dimensional vector.
    ///
    /// \param name The name of the value.
    ///
    /// \returns The read value.
    virtual Vector2<> readVector2(const char* name) = 0;

    ///
    /// Reads a value as a 3-dimensional vector.
    ///
    /// \param name The name of the value.
    ///
    /// \returns The read value.
    virtual Vector3<> readVector3(const char* name) = 0;

    ///
    /// Reads a value as a 4-dimensional vector.
    ///
    /// \param name The name of the value.
    ///
    /// \returns The read value.
    virtual Vector4<> readVector4(const char* name) = 0;

    ///
    /// Reads a value as a quaternion.
    ///
    /// \param name The name of the value.
    ///
    /// \returns The read value.
    virtual Quaternion<> readQuaternion(const char* name) = 0;
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
    /// \copydoc ComponentReader::hasValue()
    bool hasValue(const char* name);

    ///
    /// \copydoc ComponentReader::readNumber()
    double readNumber(const char* name);

    ///
    /// \copydoc ComponentReader::readString()
    std::string readString(const char* name);

    ///
    /// \copydoc ComponentReader::readVector2()
    Vector2<> readVector2(const char* name);

    ///
    /// \copydoc ComponentReader::readVector3()
    Vector3<> readVector3(const char* name);

    ///
    /// \copydoc ComponentReader::readVector4()
    Vector4<> readVector4(const char* name);

    ///
    /// \copydoc ComponentReader::readQuaternion()
    Quaternion<> readQuaternion(const char* name);

private:
    const DataValue* _dataValue;
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
    /// \copydoc ComponentReader::hasValue()
    bool hasValue(const char* name);

    ///
    /// \copydoc ComponentReader::readNumber()
    double readNumber(const char* name);

    ///
    /// \copydoc ComponentReader::readString()
    std::string readString(const char* name);

    ///
    /// \copydoc ComponentReader::readVector2()
    Vector2<> readVector2(const char* name);

    ///
    /// \copydoc ComponentReader::readVector3()
    Vector3<> readVector3(const char* name);

    ///
    /// \copydoc ComponentReader::readVector4()
    Vector4<> readVector4(const char* name);

    ///
    /// \copydoc ComponentReader::readQuaternion()
    Quaternion<> readQuaternion(const char* name);

private:
    ReadStream* _stream;
};

}