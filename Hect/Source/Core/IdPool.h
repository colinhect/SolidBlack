#pragma once

namespace hect
{

///
/// Maintains a pool of unique identifiers.
template <typename T>
class IdPool
{
public:

    ///
    /// Constructs an id pool.
    IdPool();

    ///
    /// Creates a new unique id.
    T create();

    ///
    /// Destroys an id allowing it to be reused.
    ///
    /// \param id The id to destroy.
    void destroy(T id);

private:
    T _nextId;
    std::queue<T> _nextIds;
};

}

#include "IdPool.inl"