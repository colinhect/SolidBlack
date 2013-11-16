#pragma once

namespace hect
{

///
/// A box.
template <typename T = double>
class Box
{
public:

    ///
    /// Constructs the box given its scale.
    ///
    /// \param scale The scale in all three dimensions.
    Box(const Vector3<T>& scale);

    ///
    /// Returns the scale.
    const Vector3<T>& scale() const;

private:
    Vector3<T> _scale;
};

}

#include "Box.inl"