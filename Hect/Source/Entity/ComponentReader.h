#pragma once

namespace hect
{

///
/// Provides access for reading values from a component serialization medium.
class ComponentReader :
    public Uncopyable
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

class DataValueComponentReader :
    public ComponentReader
{
public:
    DataValueComponentReader(const DataValue& dataValue);

    bool hasValue(const char* name);
    double readNumber(const char* name);
    std::string readString(const char* name);
    Vector2<> readVector2(const char* name);
    Vector3<> readVector3(const char* name);
    Vector4<> readVector4(const char* name);
    Quaternion<> readQuaternion(const char* name);

private:
    const DataValue* _dataValue;
};

class BinaryComponentReader :
    public ComponentReader
{
public:
    BinaryComponentReader(ReadStream& stream);

    bool hasValue(const char* name);
    double readNumber(const char* name);
    std::string readString(const char* name);
    Vector2<> readVector2(const char* name);
    Vector3<> readVector3(const char* name);
    Vector4<> readVector4(const char* name);
    Quaternion<> readQuaternion(const char* name);

private:
    ReadStream* _stream;
};

}