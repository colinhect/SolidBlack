#pragma once

namespace hect
{

///
/// A sphere.
template <typename T = double>
class Sphere
{
public:

    ///
    /// Constructs a sphere with a radius of one.
    Sphere();

    ///
    /// Constructs a sphere given its radius
    ///
    /// \param radius The radius of the sphere.
    Sphere(T radius);

    ///
    /// Returns the radius.
    T radius() const;

    ///
    /// Sets the radius.
    ///
    /// \param radius The new radius.
    void setRadius(T radius);

private:
    T _radius;
};

}

#include "Sphere.inl"