namespace hect
{

template <typename T>
Angle<T> Angle<T>::fromDegrees(T degrees)
{
    return Angle(((T)pi / (T)180) * degrees);
}

template <typename T>
Angle<T> Angle<T>::fromRadians(T radians)
{
    return Angle(radians);
}

template <typename T>
Angle<T>::Angle():
    _radians(0)
{
}

template <typename T>
T Angle<T>::degrees() const
{
    T degrees = ((T)180 / (T)pi) * _radians;
    if (degrees == (T)360)
    {
        degrees = (T)0;
    }
    return degrees;
}

template <typename T>
T Angle<T>::radians() const
{
    return _radians;
}

template <typename T>
Angle<T> Angle<T>::operator+(const Angle& a) const
{
    return Angle(_radians + a._radians);
}

template <typename T>
Angle<T> Angle<T>::operator-(const Angle& a) const
{
    return Angle(_radians - a._radians);
}

template <typename T>
Angle<T> Angle<T>::operator*(T value) const
{
    return Angle(_radians * value);
}

template <typename T>
Angle<T> Angle<T>::operator/(T value) const
{
    return Angle(_radians / value);
}

template <typename T>
Angle<T> Angle<T>::operator-() const
{
    return Angle(-_radians);
}

template <typename T>
Angle<T>& Angle<T>::operator+=(const Angle& a)
{
    _radians += a._radians;
    return *this;
}

template <typename T>
Angle<T>& Angle<T>::operator-=(const Angle& a)
{
    _radians -= a._radians;
    return *this;
}

template <typename T>
Angle<T>& Angle<T>::operator*=(T value)
{
    _radians *= value;
    return *this;
}

template <typename T>
Angle<T>& Angle<T>::operator/=(T value)
{
    _radians /= value;
    return *this;
}

template <typename T>
Angle<T>::Angle(T radians):
    _radians(radians)
{
}

}