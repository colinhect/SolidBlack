#pragma once

namespace hect
{

class Transform;

///
/// A camera component.
class Camera :
    public Component<Camera>
{
public:

    ///
    /// Constructs a camera component with sensible default values.
    Camera();

    ///
    /// Transforms the camera to a transformation.
    ///
    /// \param transform The transformation to transform to.
    void transformTo(const Transform& transform);

    ///
    /// Returns the front vector.
    const Vector3<>& front() const;

    ///
    /// Returns the up vector.
    const Vector3<>& up() const;

    ///
    /// Returns the right vector.
    const Vector3<>& right() const;

    ///
    /// Returns the position.
    const Vector3<>& position() const;

    ///
    /// Returns the view matrix.
    const Matrix4<>& viewMatrix() const;

    ///
    /// Returns the projection matrix.
    const Matrix4<>& projectionMatrix() const;

    ///
    /// Returns the horizontal field of view.
    Angle<> fieldOfView() const;

    ///
    /// Sets the horizontal field of view.
    ///
    /// \param fieldOfView The new horizontal field of view.
    void setFieldOfView(Angle<> fieldOfView);

    ///
    /// Returns the aspect ratio.
    double aspectRatio() const;

    ///
    /// Sets the aspect ratio.
    ///
    /// \param aspectRatio The new aspect ratio.
    void setAspectRatio(double aspectRatio);

    ///
    /// Returns the near clip distance.
    double nearClip() const;

    ///
    /// Sets the near clip distance.
    ///
    /// \param nearClip The new near clip distance.
    void setNearClip(double nearClip);

    ///
    /// Returns the far clip distance.
    double farClip() const;

    ///
    /// Sets the far clip distance.
    ///
    /// \param farClip The new far clip distance.
    void setFarClip(double farClip);

    ///
    /// Returns the frustum.
    const Frustum<>& frustum() const;

private:
    Angle<> _fieldOfView;

    double _aspectRatio;
    double _nearClip;
    double _farClip;

    Vector3<> _front;
    Vector3<> _up;
    Vector3<> _right;

    Vector3<> _position;

    Matrix4<> _viewMatrix;
    Matrix4<> _projectionMatrix;

    Frustum<> _frustum;
};

///
/// Serializer for Camera.
class CameraSerializer :
    public ComponentSerializer<Camera>
{
public:

    ///
    /// See BaseComponentSerializer::save()
    void save(const Camera& camera, DataWriter& writer) const;

    ///
    /// See BaseComponentSerializer::load()
    void load(Camera& camera, DataReader& reader, AssetCache& assetCache) const;
};

}