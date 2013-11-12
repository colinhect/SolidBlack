namespace hect
{

///
/// A format that is read from JSON text.
class JsonFormat
{
public:

    ///
    /// Parses a 2-dimensional vector from a data value.
    ///
    /// \param dataValue The data value.
    ///
    /// \returns The parsed vector.
    Vector2<> parseVector2(const DataValue& dataValue) const;

    ///
    /// Parses a 3-dimensional vector from a data value.
    ///
    /// \param dataValue The data value.
    ///
    /// \returns The parsed vector.
    Vector3<> parseVector3(const DataValue& dataValue) const;

    ///
    /// Parses a 4-dimensional vector from a data value.
    ///
    /// \param dataValue The data value.
    ///
    /// \returns The parsed vector.
    Vector4<> parseVector4(const DataValue& dataValue) const;

    ///
    /// Parses a 4 vy 4 matrix from a data value.
    ///
    /// \param dataValue The data value.
    ///
    /// \returns The parsed matrix.
    Matrix4<> parseMatrix4(const DataValue& dataValue) const;
};

}