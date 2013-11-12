namespace hect
{

///
/// A pyramid with a near and far plane cutting the top and bottom.
///
/// \remarks Useful for check if objects are with the bounds of a camera.
template <typename T = double>
class Frustum
{
public:

    ///
    /// A plane of the frustm.
    enum Plane
    {
        ///
        /// The top plane.
        Top,

        ///
        /// The bottom plane.
        Bottom,

        ///
        /// The left plane.
        Left,

        ///
        /// The right plane
        Right,

        ///
        /// The far plane.
        Far,

        ///
        /// The near plane.
        Near
    };

    ///
    /// The result of a frustum test.
    enum TestResult
    {
        ///
        /// The tested geometry is outside of the frustum.
        Outside,

        ///
        /// The tested geometry is completely inside of the frustum.
        Inside,

        ///
        /// The tested geometry is partially inside of the frustum.
        Intersect
    };

    ///
    /// Constructs a default frustum.
    Frustum();

    ///
    /// Constructs a frustum
    ///
    /// \param position The position.
    /// \param front The front direction.
    /// \param up The up direction.
    /// \param fieldOfView The horizontal angle.
    /// \param aspectRatio The ratio of width and height.
    /// \param nearClip The distance from the position to begin the
    /// frustum.
    /// \param farClip The distance from the position to end the frustum.
    Frustum(
        const Vector3<T>& position,
        const Vector3<T>& front,
        const Vector3<T>& up,
        Angle<T> fieldOfView,
        T aspectRatio,
        T nearClip,
        T farClip);

    ///
    /// Tests an axis aligned box against the frustum.
    ///
    /// \param box The box.
    ///
    /// \returns The test result.
    TestResult testAxisAlignedBox(const AxisAlignedBox<T>& box) const;

private:
    hect::Plane<T> _planes[6];
    Vector3<T> _position;
};

}

#include "Frustum.inl"