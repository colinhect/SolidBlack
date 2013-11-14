namespace hect
{

///
/// A plane in 3-dimensional space.
template <typename T = double>
class Plane
{
public:

    ///
    /// Constructs a plane from 3 points.
    ///
    /// \param p0 The first point.
    /// \param p1 The second point.
    /// \param p2 The third point.
    static Plane fromPoints(const Vector3<T>& p0, const Vector3<T>& p1, const Vector3<T>& p2);

    ///
    /// Constructs a default plane.
    Plane();

    ///
    /// Constructs a plane given a position, normal, and distance.
    ///
    /// \param position The origin of the plane.
    /// \param normal The direction from the origin the plane faces.
    /// \param distance The distance from the origin along the normal.
    Plane(const Vector3<T>& position, const Vector3<T>& normal, T distance);

    ///
    /// Returns the position.
    const Vector3<T>& position() const;

    ///
    /// Returns the normal.
    const Vector3<T>& normal() const;

    ///
    /// Returns the distance.
    T distance() const;

private:
    Vector3<T> _position;
    Vector3<T> _normal;
    T _distance;
};

}

#include "Plane.inl"