#pragma once

namespace hect
{

///
/// A fixed-size bit field.
template <typename T>
class BitField
{
public:

    ///
    /// Constructs a bit field with all bits set to zero.
    BitField();

    ///
    /// Constructs a bit field with initial data.
    ///
    /// \param data The initial data.
    BitField(T data);

    ///
    /// Sets a bit to 0 or 1.
    ///
    /// \param bitIndex The index of the bit to set.
    /// \param value True if setting the bit to 1; false if 0.
    void set(size_t bitIndex, bool value);

    ///
    /// Returns true if a bit is 1; false if it is 0.
    ///
    /// \param bitIndex The index of the bit to get.
    bool get(size_t bitIndex) const;

    ///
    /// Returns whether the bit field contains the same bits bits as another.
    ///
    /// \param bitField The bit field.
    bool contains(const BitField& bitField) const;

    ///
    /// Clears the bit field to be all zeros.
    void clear();

    ///
    /// Casts the bit field to its underlying type.
    operator T() const;

private:
    T _data;
};

}

#include "BitField.inl"