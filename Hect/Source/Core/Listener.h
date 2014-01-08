#pragma once

namespace hect
{

///
/// An listener of specific events.
template <typename T>
class Listener
{
public:

    ///
    /// Notifies the listener of an event.
    ///
    /// \param event The event.
    virtual void receiveEvent(const T& event) = 0;
};

}