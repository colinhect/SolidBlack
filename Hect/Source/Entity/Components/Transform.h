#pragma once

namespace hect
{

///
/// A combination of a position, scale, and rotation.
class Transform :
    public Component<Transform>
{
public:

    ///
    /// Constructs an identity transform component.
    Transform();

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

///
/// Serializer for Transform.
class TransformSerializer :
    public ComponentSerializer<Transform>
{
public:

    ///
    /// See BaseComponentSerializer::save()
    void save(const Transform& transform, DataWriter& writer) const;

    ///
    /// See BaseComponentSerializer::load()
    void load(Transform& transform, DataReader& reader, AssetCache& assetCache) const;
};

}