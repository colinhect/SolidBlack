#include "Hect.h"

using namespace hect;

Camera::Camera() :
    _fieldOfView(Angle<>::fromDegrees(90)),
    _aspectRatio(1),
    _nearClip(0.1),
    _farClip(1000),
    _front(-Vector3<>::unitZ()),
    _up(Vector3<>::unitY()),
    _right(_front.cross(_up).normalized())
{
}

Camera::Camera(Angle<> fieldOfView, double aspectRatio, double nearClip, double farClip) :
    _fieldOfView(fieldOfView),
    _aspectRatio(aspectRatio),
    _nearClip(nearClip),
    _farClip(farClip),
    _front(-Vector3<>::unitZ()),
    _up(Vector3<>::unitY()),
    _right(_front.cross(_up).normalized())
{
}

void Camera::transformTo(const Transform& transform)
{
    const Vector3<>& position = transform.position();
    const Quaternion<>& rotation = transform.rotation();

    _front = (rotation * -Vector3<>::unitZ()).normalized();
    _up = (rotation * Vector3<>::unitY()).normalized();
    _right = _front.cross(_up).normalized();

    _position = position;

    _viewMatrix = Matrix4<>::createView(position, _front, _up);
    _projectionMatrix = Matrix4<>::createPerspective(_fieldOfView, _aspectRatio, _nearClip, _farClip);

    _frustum = Frustum<>(position, _front, _up, _fieldOfView, _aspectRatio, _nearClip, _farClip);
}

const Vector3<>& Camera::front() const
{
    return _front;
}

const Vector3<>& Camera::up() const
{
    return _up;
}

const Vector3<>& Camera::right() const
{
    return _right;
}

const Vector3<>& Camera::position() const
{
    return _position;
}

const Matrix4<>& Camera::viewMatrix() const
{
    return _viewMatrix;
}

const Matrix4<>& Camera::projectionMatrix() const
{
    return _projectionMatrix;
}

Angle<> Camera::fieldOfView() const
{
    return _fieldOfView;
}

void Camera::setFieldOfView(Angle<> fieldOfView)
{
    _fieldOfView = fieldOfView;
}

double Camera::aspectRatio() const
{
    return _aspectRatio;
}

void Camera::setAspectRatio(double aspectRatio)
{
    _aspectRatio = aspectRatio;
}

double Camera::nearClip() const
{
    return _nearClip;
}

void Camera::setNearClip(double nearClip)
{
    _nearClip = nearClip;
}

double Camera::farClip() const
{
    return _farClip;
}

void Camera::setFarClip(double farClip)
{
    _farClip = farClip;
}

const Frustum<>& Camera::frustum() const
{
    return _frustum;
}

void CameraSerializer::fromDataValue(Camera& camera, const DataValue& dataValue, AssetCache& assetCache) const
{
    // Field of view
    const DataValue& fieldOfView = dataValue["fieldOfView"];
    if (fieldOfView.isNumber())
    {
        camera.setFieldOfView(Angle<>::fromDegrees(fieldOfView.asDouble()));
    }

    // Aspect ratio
    const DataValue& aspectRatio = dataValue["aspectRatio"];
    if (aspectRatio.isNumber())
    {
        camera.setAspectRatio(aspectRatio.asDouble());
    }

    // Near clip
    const DataValue& nearClip = dataValue["nearClip"];
    if (nearClip.isNumber())
    {
        camera.setNearClip(nearClip.asDouble());
    }

    // Far clip
    const DataValue& farClip = dataValue["farClip"];
    if (farClip.isNumber())
    {
        camera.setFarClip(farClip.asDouble());
    }
}

DataValue CameraSerializer::toDataValue(const Camera& camera) const
{
    // Field of view
    DataValue::Object members;
    members["fieldOfView"] = camera.fieldOfView().degrees();

    return DataValue(members);
}