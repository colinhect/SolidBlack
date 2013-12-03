#pragma once

namespace hect
{

///
/// Provides access for writing values to a component serialization medium.
class ComponentWriter :
    public Uncopyable
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

class DataValueComponentWriter :
    public ComponentWriter
{
public:
    void writeNumber(const char* name, double value);
    void writeString(const char* name, const std::string& value);
    void writeVector2(const char* name, const Vector2<>& value);
    void writeVector3(const char* name, const Vector3<>& value);
    void writeVector4(const char* name, const Vector4<>& value);
    void writeQuaternion(const char* name, const Quaternion<>& value);

    DataValue dataValue() const;

private:
    DataValue::Object _members;
};

class BinaryComponentWriter :
    public ComponentWriter
{
public:
    BinaryComponentWriter(WriteStream& stream);

    void writeNumber(const char* name, double value);
    void writeString(const char* name, const std::string& value);
    void writeVector2(const char* name, const Vector2<>& value);
    void writeVector3(const char* name, const Vector3<>& value);
    void writeVector4(const char* name, const Vector4<>& value);
    void writeQuaternion(const char* name, const Quaternion<>& value);

private:
    WriteStream* _stream;
};

}