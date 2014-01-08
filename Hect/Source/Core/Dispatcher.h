#pragma once

namespace hect
{

///
/// An event dispatcher which notifies registered listeners of specific events.
template <typename T>
class Dispatcher
{
public:

    ///
    /// Registers a listener to receive events notified from the dispatcher.
    ///
    /// \note If the listener is already registered to the dispatcher then
    /// there is no effect.
    ///
    /// \param listener The listener to register.
    void addListener(Listener<T>& listener);
    
    ///
    /// Unregisters a listener from receiving events notified from the
    /// dispatcher.
    ///
    /// \note If the listener is not registered to the dispatcher then there is
    /// no effect.
    ///
    /// \param listener The listener to unregister.
    void removeListener(Listener<T>& listener);

    ///
    /// Notifies an event to all registered listeners.
    ///
    /// \param event The event.
    void notifyEvent(const T& event);

private:
    std::vector<Listener<T>*> _listeners;
};

}

#include "Dispatcher.inl"