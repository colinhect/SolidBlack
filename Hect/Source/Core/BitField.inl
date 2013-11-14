namespace hect
{

template <typename T>
BitField<T>::BitField() :
    _data(0)
{
}

template <typename T>
BitField<T>::BitField(T data) :
    _data(data)
{
}

template <typename T>
void BitField<T>::set(size_t bitIndex, bool value)
{
    assert(bitIndex < sizeof(T) * 8);
    T bit = ((T)1) << bitIndex;
    if (value)
    {
        _data |= bit;
    }
    else
    {
        _data &= ~bit;
    }
}

template <typename T>
bool BitField<T>::get(size_t bitIndex) const
{
    assert(bitIndex < sizeof(T) * 8);
    T bit = ((T)1) << bitIndex;
    return (_data & bit) == bit;
}

template <typename T>
bool BitField<T>::contains(const BitField& bitField) const
{
    return (_data & bitField._data) == bitField._data;
}

template <typename T>
void BitField<T>::clear()
{
    _data = 0;
}

template <typename T>
BitField<T>::operator T() const
{
    return _data;
}

}