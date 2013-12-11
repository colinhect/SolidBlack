#include "Hect.h"

using namespace hect;

Transform::Transform() :
    _dirtyBits(0),
    _scale(Vector3<>::one())
{
}

void Transform::buildMatrix(Matrix4<>& matrix) const
{
    matrix = Matrix4<>();

    if (_dirtyBits & PositionBit)
    {
        matrix.translate(_position);
    }

    if (_dirtyBits & ScaleBit)
    {
        matrix.scale(_scale);
    }

    if (_dirtyBits & RotationBit)
    {
        matrix.rotate(_rotation);
    }
}

void Transform::translate(const Vector3<>& translation)
{
    _position += translation;
    _dirtyBits |= PositionBit;
}

void Transform::scale(const Vector3<>& scale)
{
    _scale *= scale;
    _dirtyBits |= ScaleBit;
}

void Transform::rotateGlobal(const Quaternion<>& rotation)
{
    _rotation *= rotation;
    _rotation.normalize();
    _dirtyBits |= RotationBit;
}

void Transform::rotateGlobal(const Vector3<>& axis, Angle<> angle)
{
    rotateGlobal(Quaternion<>::fromAxisAngle(axis, angle));
}

const Vector3<>& Transform::position() const
{
    return _position;
}

void Transform::setPosition(const Vector3<>& position)
{
    _position = position;
    _dirtyBits |= PositionBit;
}

const Vector3<>& Transform::scale() const
{
    return _scale;
}

void Transform::setScale(const Vector3<>& scale)
{
    _scale = scale;
    _dirtyBits |= ScaleBit;
}

const Quaternion<>& Transform::rotation() const
{
    return _rotation;
}

void Transform::setRotation(const Quaternion<>& rotation)
{
    _rotation = rotation;
    _dirtyBits |= RotationBit;
}

void Transform::transformBy(const Transform& transform)
{
    _position = transform._rotation * _position;
    _position += transform._position;
    _scale *= transform._scale;
    _rotation = transform._rotation * _rotation;
    _dirtyBits = PositionBit | ScaleBit | RotationBit;
}

void TransformSerializer::save(const Transform& transform, DataWriter& writer) const
{
    Vector3<> axis;
    Angle<> angle;
    transform.rotation().toAxisAngle(axis, angle);

    writer.writeVector3("position", transform.position());
    writer.writeVector3("scale", transform.scale());
    writer.beginObject("rotation");
    writer.writeVector3("axis", axis);
    writer.writeDouble("angle", angle.degrees());
    writer.endObject();
}

void TransformSerializer::load(Transform& transform, DataReader& reader, AssetCache& assetCache) const
{
    assetCache;

    if (reader.hasMember("position"))
    {
        transform.setPosition(reader.readVector3("position"));
    }

    if (reader.hasMember("scale"))
    {
        transform.setScale(reader.readVector3("scale"));
    }

    if (reader.beginObject("rotation"))
    {
        Vector3<> axis;
        Angle<> angle;

        if (reader.hasMember("axis"))
        {
            axis = reader.readVector3("axis");
        }

        if (reader.hasMember("angle"))
        {
            double degrees = reader.readDouble("angle");
            angle = Angle<>::fromDegrees(degrees);
        }

        transform.setRotation(Quaternion<>::fromAxisAngle(axis, angle));
        reader.endObject();
    }
}