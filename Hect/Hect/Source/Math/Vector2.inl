namespace hect
{

template <typename T>
Vector2<T> Vector2<T>::zero()
{
    return Vector2(0);
}

template <typename T>
Vector2<T> Vector2<T>::one()
{
    return Vector2(1);
}

template <typename T>
Vector2<T> Vector2<T>::unitX()
{
    return Vector2(1, 0);
}

template <typename T>
Vector2<T> Vector2<T>::unitY()
{
    return Vector2(0, 1);
}

template <typename T>
Vector2<T>::Vector2() :
    x(0),
    y(0)
{
}

template <typename T>
Vector2<T>::Vector2(T value) :
    x(value),
    y(value)
{
}

template <typename T>
Vector2<T>::Vector2(T x, T y) :
    x(x),
    y(y)
{
}

template <typename T>
void Vector2<T>::normalize()
{
    T inv = (T)1.0 / length();
    *this *= inv;
}

template <typename T>
Vector2<T> Vector2<T>::normalized() const
{
    Vector2 v(*this);
    v.normalize();
    return v;
}

template <typename T>
T Vector2<T>::dot(const Vector2& v) const
{
    return x * v.x + y * v.y;
}

template <typename T>
Angle<T> Vector2<T>::angleFrom(const Vector2& v) const
{
    T radians = (T)std::acos(dot(v));
    return Angle<T>::fromRadians(radians);
}

template <typename T>
T Vector2<T>::length() const
{
    return (T)std::sqrt(lengthSquared());
}

template <typename T>
T Vector2<T>::lengthSquared() const
{
    return dot(*this);
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2& v) const
{
    return Vector2(x + v.x, y + v.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2& v) const
{
    return Vector2(x - v.x, y - v.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(T value) const
{
    return Vector2(x * value, y * value);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const Vector2& v) const
{
    return Vector2(x * v.x, y * v.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(T value) const
{
    return Vector2(x / value, y / value);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const Vector2& v) const
{
    return Vector2(x / v.x, y / v.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator-() const
{
    return Vector2(-x, -y);
}

template <typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(T value)
{
    x *= value;
    y *= value;
    return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(const Vector2& v)
{
    x *= v.x;
    y *= v.y;
    return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(T value)
{
    x /= value;
    y /= value;
    return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(const Vector2& v)
{
    x /= v.x;
    y /= v.y;
    return *this;
}

template <typename T>
T& Vector2<T>::operator[](size_t i)
{
    assert(i < 2);
    return ((T*)this)[i];
}

template <typename T>
const T& Vector2<T>::operator[](size_t i) const
{
    assert(i < 2);
    return ((const T*)this)[i];
}

}