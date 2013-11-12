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
    void writeSigned8(int8_t value);

    ///
    /// Writes an unsigned 8-bit integer.
    ///
    /// \param value The value to write.
    void writeUnsigned8(uint8_t value);

    ///
    /// Writes a signed 16-bit integer.
    ///
    /// \param value The value to write.
    void writeSigned16(int16_t value);

    ///
    /// Writes an unsigned 16-bit integer.
    ///
    /// \param value The value to write.
    void writeUnsigned16(uint16_t value);

    ///
    /// Writes a signed 32-bit integer.
    ///
    /// \param value The value to write.
    void writeSigned32(int32_t value);

    ///
    /// Writes an unsigned 32-bit integer.
    ///
    /// \param value The value to write.
    void writeUnsigned32(uint32_t value);

    ///
    /// Writes a signed 64-bit integer.
    ///
    /// \param value The value to write.
    void writeSigned64(int64_t value);

    ///
    /// Writes an unsigned 64-bit integer.
    ///
    /// \param value The value to write.
    void writeUnsigned64(uint64_t value);

    ///
    /// Writes a 32-bit float.
    ///
    /// \param value The value to write.
    void writeFloat32(float value);

    ///
    /// Writes a 64-bit float
    ///
    /// \param value The value to write.
    void writeFloat64(double value);

};

}