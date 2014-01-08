#pragma once

namespace hect
{

///
/// An observer of specific events.
template <typename T>
class Observer
{
public:

    ///
    /// Notifies the observer of an event.
    ///
    /// \param event The event.
    virtual void receiveEvent(const T& event) { event; }
};

}