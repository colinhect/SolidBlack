#include "Hect.h"

using namespace hect;

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