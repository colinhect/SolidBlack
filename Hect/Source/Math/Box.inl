namespace hect
{

template <typename T>
Box<T>::Box(const Vector3<T>& scale) :
    _scale(scale)
{
}

template <typename T>
const Vector3<T>& Box<T>::scale() const
{
    return _scale;
}

}