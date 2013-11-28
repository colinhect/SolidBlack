namespace hect
{

template <typename T>
Sphere<T>::Sphere() :
    _radius(1)
{
}

template <typename T>
Sphere<T>::Sphere(T radius) :
    _radius(radius)
{
}

template <typename T>
T Sphere<T>::radius() const
{
    return _radius;
}

template <typename T>
void Sphere<T>::setRadius(T radius)
{
    _radius = radius;
}

}