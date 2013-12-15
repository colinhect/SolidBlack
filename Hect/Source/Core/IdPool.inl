namespace hect
{

template <typename T>
IdPool<T>::IdPool() :
    _nextId(0)
{
}

template <typename T>
T IdPool<T>::create()
{
    T id;
    if (!_nextIds.empty())
    {
        id = _nextIds.back();
        _nextIds.pop();
    }
    else
    {
        id = _nextId++;
    }

    return id;
}

template <typename T>
void IdPool<T>::destroy(T id)
{
    _nextIds.push(id);
}

}