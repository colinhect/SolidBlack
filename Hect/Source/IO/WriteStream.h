#pragma once

namespace hect
{

///
/// An interface for writing streamed data.
class WriteStream
{
public:

    ///
    /// Writes raw bytes to the stream.
    ///
    /// \param bytes A pointer to the bytes to write.
    /// \param byteCount The number of bytes to write.
    virtual void writeBytes(const uint8_t* bytes, size_t byteCount) = 0;

    ///
    /// Writes a string with its length prepended as an unsigned 32-bit
    /// integer.
    ///
    /// \param string The string to write.
    void writeString(const std::string& string);

    ///
    /// Writes a signed 8-bit integer.
    ///
    /// \param value The value to write.
    void writeByte(int8_t value);

    ///
    /// Writes an unsigned 8-bit integer.
    ///
    /// \param value The value to write.
    void writeUnsignedByte(uint8_t value);

    ///
    /// Writes a signed 16-bit integer.
    ///
    /// \param value The value to write.
    void writeShort(int16_t value);

    ///
    /// Writes an unsigned 16-bit integer.
    ///
    /// \param value The value to write.
    void writeUnsignedShort(uint16_t value);

    ///
    /// Writes a signed 32-bit integer.
    ///
    /// \param value The value to write.
    void writeInt(int32_t value);

    ///
    /// Writes an unsigned 32-bit integer.
    ///
    /// \param value The value to write.
    void writeUnsignedInt(uint32_t value);

    ///
    /// Writes a signed 64-bit integer.
    ///
    /// \param value The value to write.
    void writeLong(int64_t value);

    ///
    /// Writes an unsigned 64-bit integer.
    ///
    /// \param value The value to write.
    void writeUnsignedLong(uint64_t value);

    ///
    /// Writes a 32-bit float.
    ///
    /// \param value The value to write.
    void writeFloat(float value);

    ///
    /// Writes a 64-bit float
    ///
    /// \param value The value to write.
    void writeDouble(double value);
    
    ///
    /// Writes a 2-dimensional vector.
    ///
    /// \param value The vector to write.
    void writeVector2(const Vector2<>& value);

    ///
    /// Writes a 3-dimensional vector.
    ///
    /// \param value The vector to write.
    void writeVector3(const Vector3<>& value);

    ///
    /// Writes a 4-dimensional vector.
    ///
    /// \param value The vector to write.
    void writeVector4(const Vector4<>& value);

    ///
    /// Writes a quaternion.
    ///
    /// \param value The quaternion to write.
    void writeQuaternion(const Quaternion<>& value);

};

}