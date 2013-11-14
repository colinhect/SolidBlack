namespace hect
{

template <typename T>
AxisAlignedBox<T>::AxisAlignedBox() :
    _flags(0)
{
}

template <typename T>
AxisAlignedBox<T>::AxisAlignedBox(const Vector3<T>& minimum, const Vector3<T>& maximum) :
    _flags(MinX | MinY | MinZ | MaxX | MaxY | MaxZ),
    _minimum(minimum),
    _maximum(maximum)
{
}

template <typename T>
void AxisAlignedBox<T>::expandToInclude(const Vector3<T>& point)
{
    _mergeMinimum(point);
    _mergeMaximum(point);
}

template <typename T>
void AxisAlignedBox<T>::expandToInclude(const AxisAlignedBox<T>& box)
{
    if (!box.hasSize())
    {
        return;
    }
    else if (!hasSize())
    {
        *this = box;
        return;
    }

    _mergeMinimum(box._minimum);
    _mergeMaximum(box._maximum);
}

template <typename T>
const Vector3<T>& AxisAlignedBox<T>::minimum() const
{
    return _minimum;
}

template <typename T>
const Vector3<T>& AxisAlignedBox<T>::maximum() const
{
    return _maximum;
}

template <typename T>
bool AxisAlignedBox<T>::hasSize() const
{
    return _flags != 0;
}

template <typename T>
void AxisAlignedBox<T>::_mergeMinimum(const Vector3<T>& point)
{
    if (!(_flags & MinX) || point.x < _minimum.x)
    {
        _minimum.x = point.x;
        _flags |= MinX;
    }

    if (!(_flags & MinY) || point.y < _minimum.y)
    {
        _minimum.y = point.y;
        _flags |= MinY;
    }

    if (!(_flags & MinZ) || point.z < _minimum.z)
    {
        _minimum.z = point.z;
        _flags |= MinZ;
    }
}

template <typename T>
void AxisAlignedBox<T>::_mergeMaximum(const Vector3<T>& point)
{
    if (!(_flags & MaxX) || point.x > _maximum.x)
    {
        _maximum.x = point.x;
        _flags |= MaxX;
    }

    if (!(_flags & MaxY) || point.y > _maximum.y)
    {
        _maximum.y = point.y;
        _flags |= MaxY;
    }

    if (!(_flags & MaxZ) || point.z > _maximum.z)
    {
        _maximum.z = point.z;
        _flags |= MaxZ;
    }
}

}