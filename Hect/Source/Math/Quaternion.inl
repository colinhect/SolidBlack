namespace hect
{

template <typename T>
Quaternion<T> Quaternion<T>::fromAxisAngle(const Vector3<T>& axis, Angle<T> angle)
{
    T halfRadians = angle.radians() / (T)2.0;

    Vector3<T> v = axis.normalized() * (T)std::sin(halfRadians);
    T w = (T)std::cos(halfRadians);

    return Quaternion(v, w).normalized();
}

template <typename T>
Quaternion<T>::Quaternion() :
    x(0),
    y(0),
    z(0),
    w(1)
{
}

template <typename T>
Quaternion<T>::Quaternion(T x, T y, T z, T w) :
    x(x),
    y(y),
    z(z),
    w(w)
{
}

template <typename T>
Quaternion<T>::Quaternion(const Vector3<T>& v, T w) :
    x(v.x),
    y(v.y),
    z(v.z),
    w(w)
{
}

template <typename T>
Quaternion<T>::Quaternion(const Vector4<T>& v) :
    x(v.x),
    y(v.y),
    z(v.z),
    w(v.w)
{
}

template <typename T>
void Quaternion<T>::normalize()
{
    T inv = (T)1.0 / length();
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
}

template <typename T>
Quaternion<T> Quaternion<T>::normalized() const
{
    Quaternion q(*this);
    q.normalize();
    return q;
}

template <typename T>
T Quaternion<T>::dot(const Quaternion& q) const
{
    return x * q.x + y * q.y + z * q.z + w * q.w;
}

template <typename T>
T Quaternion<T>::length() const
{
    return (T)std::sqrt(lengthSquared());
}

template <typename T>
T Quaternion<T>::lengthSquared() const
{
    return dot(*this);
}

template <typename T>
Quaternion<T> Quaternion<T>::conjugate() const
{
    return Quaternion(-x, -y, -z, w);
}

template <typename T>
Quaternion<T> Quaternion<T>::inverse() const
{
    T inv = 1.0 / length();
    return Quaternion(-(x * inv), -(y * inv), -(z * inv), w * inv);
}

template <typename T>
void Quaternion<T>::toAxisAngle(Vector3<T>* axis, Angle<T>* angle)
{
    assert(axis);
    assert(angle);

    Quaternion q(*this);
    q.normalize();

    axis->x = q.x;
    axis->y = q.y;
    axis->z = q.z;
    axis->normalize();

    *angle = Angle<T>::fromRadians((T)2.0 * (T)std::acos(w));
}

template <typename T>
Quaternion<T> Quaternion<T>::operator*(T value) const
{
    return Quaternion(x * value, y * value, z * value, w * value);
}

template <typename T>
Vector3<T> Quaternion<T>::operator*(const Vector3<T>& v) const
{
    return Matrix4<T>::fromRotation(*this) * v;
}

template <typename T>
Quaternion<T> Quaternion<T>::operator*(const Quaternion& q) const
{
    Vector3<T> av(x, y, z);
    Vector3<T> bv(q.x, q.y, q.z);

    Vector3<T> newV = (bv * w) + (av * q.w) + av.cross(bv);
    T newW = w * q.w - av.dot(bv);

    return Quaternion<T>(newV, newW);
}

template <typename T>
Quaternion<T> Quaternion<T>::operator-() const
{
    return Quaternion(-x, -y, -z, -w);
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator*=(T value)
{
    x *= value;
    y *= value;
    z *= value;
    w *= value;
    return *this;
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator*=(const Quaternion& q)
{
    return *this = *this * q;
}

template <typename T>
T& Quaternion<T>::operator[](size_t i)
{
    assert(i < 4);
    return ((T*)this)[i];
}

template <typename T>
const T& Quaternion<T>::operator[](size_t i) const
{
    assert(i < 4);
    return ((const T*)this)[i];
}

}