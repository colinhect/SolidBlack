namespace hect
{

template <typename T>
Plane<T> Plane<T>::fromPoints(const Vector3<T>& p0, const Vector3<T>& p1, const Vector3<T>& p2)
{
    Vector3<T> position = p1;
    Vector3<T> normal = (p2 - p1).cross(p0 - p1).normalized();
    T distance = -normal.dot(position);

    return Plane<T>(position, normal, distance);
}

template <typename T>
Plane<T>::Plane() :
    _distance(0)
{
}

template <typename T>
Plane<T>::Plane(const Vector3<T>& position, const Vector3<T>& normal, T distance) :
    _position(position),
    _normal(normal),
    _distance(distance)
{
}

template <typename T>
const Vector3<T>& Plane<T>::position() const
{
    return _position;
}

template <typename T>
const Vector3<T>& Plane<T>::normal() const
{
    return _normal;
}

template <typename T>
T Plane<T>::distance() const
{
    return _distance;
}

}