#pragma once

namespace hect
{

///
/// A box aligned with the global axes.
template <typename T = double>
class AxisAlignedBox
{
public:

    ///
    /// Constructs an axis aligned box at the origin without a size.
    AxisAlignedBox();

    ///
    /// Constructs an axis aligned box given a minimum and maximum point.
    ///
    /// \param minimum The minimum point.
    /// \param maximum The maximum point.
    AxisAlignedBox(const Vector3<T>& minimum, const Vector3<T>& maximum);

    ///
    /// Expands the bounds of the box to include point.
    ///
    /// \param point The point to include.
    void expandToInclude(const Vector3<T>& point);

    ///
    /// Expands the bounds of the box to include another box.
    ///
    /// \param box The box to include.
    void expandToInclude(const AxisAlignedBox<T>& box);

    ///
    /// Returns the minimum point.
    const Vector3<T>& minimum() const;

    ///
    /// Returns the maximum point.
    const Vector3<T>& maximum() const;

    ///
    /// Returns whether the box has a non-negligible size.
    bool hasSize() const;

    ///
    /// Converts to an equivalent vector with a different underlying type.
    template <typename U>
    operator AxisAlignedBox<U>() const
    {
        return AxisAlignedBox<U>(_minimum, _maximum);
    }

private:
    void _mergeMinimum(const Vector3<T>& point);
    void _mergeMaximum(const Vector3<T>& point);

    enum Flags
    {
        MinX = 1,
        MinY = 2,
        MinZ = 4,
        MaxX = 8,
        MaxY = 16,
        MaxZ = 32
    };

    int _flags;

    Vector3<T> _minimum;
    Vector3<T> _maximum;
};

}

#include "AxisAlignedBox.inl"