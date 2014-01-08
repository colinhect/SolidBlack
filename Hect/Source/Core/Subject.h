#pragma once

namespace hect
{

///
/// A subject which propagates events to registers observers.
template <typename T>
class Subject
{
public:

    ///
    /// Registers an observer to receive events notified from the subject.
    ///
    /// \param observer The observer to register.
    void addObserver(Observer<T>& observer);
    
    ///
    /// Unregisters an observer from receiving events notified from the subject.
    ///
    /// \note If the observer was never registered to the subject then there
    /// is no effect.
    ///
    /// \param observer The observer to unregister.
    void removeObserver(Observer<T>& observer);

    ///
    /// Notifies an event to all registered observers.
    ///
    /// \param event The event.
    void notifyEvent(const T& event);

private:
    std::vector<Observer<T>*> _observers;
};

}

#include "Subject.inl"