#pragma once

namespace hect
{

///
/// A combination of a position, scale, and rotation.
class Transform :
    public EntityComponent<Transform>
{
public:

    ///
    /// Constructs an identity transform component.
    Transform();

    ///
    /// Constructs a transform given the position.
    ///
    /// \param position The position.
    Transform(const Vector3<>& position);

    ///
    /// Constructs a transform given the position, scale, and rotation.
    ///
    /// \param position The position.
    /// \param scale The scale.
    /// \param rotation The rotation.
    Transform(const Vector3<>& position, const Vector3<>& scale, const Quaternion<>& rotation);

    ///
    /// Builds a transformation matrix.
    ///
    /// \param matrix The matrix to assign the transformation matrix to.
    void buildMatrix(Matrix4<>& matrix) const;

    ///
    /// Applies a translation to the transform.
    ///
    /// \param translation The translation to apply.
    void translate(const Vector3<>& translation);

    ///
    /// Applies a scale to the transform.
    ///
    /// \param scale The scale to apply.
    void scale(const Vector3<>& scale);

    ///
    /// Applies a global rotation to the transform.
    ///
    /// \param rotation The rotation to apply.
    void rotateGlobal(const Quaternion<>& rotation);

    ///
    /// Applies a global rotation to the transform.
    ///
    /// \param axis The axis to rotate about.
    /// \param angle The angle to rotate.
    void rotateGlobal(const Vector3<>& axis, Angle<> angle);

    ///
    /// Returns the position.
    const Vector3<>& position() const;

    ///
    /// Sets the position.
    ///
    /// \param position The new position.
    void setPosition(const Vector3<>& position);

    ///
    /// Returns the scale.
    const Vector3<>& scale() const;

    ///
    /// Sets the scale.
    ///
    /// \param scale The new scale.
    void setScale(const Vector3<>& scale);

    ///
    /// Returns the rotation.
    const Quaternion<>& rotation() const;

    ///
    /// Sets the rotation.
    ///
    /// \param rotation The new rotation.
    void setRotation(const Quaternion<>& rotation);

    ///
    /// Transforms by another transform.
    void transformBy(const Transform& transform);

private:
    enum DirtyBit
    {
        PositionBit = 1,
        ScaleBit = 2,
        RotationBit = 4
    };

    uint8_t _dirtyBits;

    Vector3<> _position;
    Vector3<> _scale;
    Quaternion<> _rotation;
};

class TransformSerializer :
    public EntityComponentSerializer<Transform>
{
public:
    void fromDataValue(Transform& transform, const DataValue& dataValue, AssetCache& assetCache) const;
    DataValue toDataValue(const Transform& transform) const;
};

}