#pragma once

namespace hect
{

///
/// An angle.
template <typename T = double>
class Angle
{
public:

    ///
    /// Constructs an angle from a value in degrees.
    ///
    /// \param degrees The angle in degrees.
    ///
    /// \returns The angle.
    static Angle fromDegrees(T degrees);

    ///
    /// Constructs an angle from a value in radians.
    ///
    /// \param radians The angle in radians.
    ///
    /// \returns The angle.
    static Angle fromRadians(T radians);

    ///
    /// Constructs a zero-degree angle.
    Angle();

    ///
    /// Returns the value of the angle in degrees.
    T toDegrees() const;

    ///
    /// Returns the value of the angle in radians.
    T toRadians() const;

    ///
    /// Returns the sum of the angle and another angle.
    ///
    /// \param a The angle to compute the sum with.
    Angle operator+(const Angle& a) const;

    ///
    /// Returns the difference of the angle and another angle.
    ///
    /// \param a The angle to compute the diference with.
    Angle operator-(const Angle& a) const;

    ///
    /// Returns the product of the angle and a scalar.
    ///
    /// \param value The scalar to compute the product with.
    Angle operator*(T value) const;

    ///
    /// Returns the quotient of the angle and a scalar.
    ///
    /// \param value The scalar to compute the quotient with.
    Angle operator/(T value) const;

    ///
    /// Returns a negated copy of the angle.
    Angle operator-() const;

    ///
    /// Adds an angle to the angle.
    ///
    /// \param a The angle to add.
    ///
    /// \returns A reference to the angle.
    Angle& operator+=(const Angle& a);

    ///
    /// Subtracts an angle from the angle.
    ///
    /// \param a The angle to subtract.
    ///
    /// \returns A reference to the angle.
    Angle& operator-=(const Angle& a);

    ///
    /// Multiples the angle by a scalar.
    ///
    /// \param value The scalar to multiply by.
    ///
    /// \returns A reference to the angle.
    Angle& operator*=(T value);

    ///
    /// Divides the angle by a scalar.
    ///
    /// \param value The scalar to divide by.
    ///
    /// \returns A reference to the angle.
    Angle& operator/=(T value);

    ///
    /// Converts to an equivalent angle with a different underlying type.
    template <typename U>
    operator Angle<U>() const
    {
        return Angle<U>::fromRadians((U)_radians);
    }

private:
    Angle(T radians);

    T _radians;
};

}

#include "Angle.inl"