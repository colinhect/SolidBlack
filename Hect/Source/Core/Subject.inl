namespace hect
{

template <typename T>
void Subject<T>::addObserver(Observer<T>& observer)
{
    if (std::find(_observers.begin(), _observers.end(), &observer) != _observers.end())
    {
        return;  // This observer was already added
    }

    _observers.push_back(&observer);
}

template <typename T>
void Subject<T>::removeObserver(Observer<T>& observer)
{
    _observers.erase(std::remove(_observers.begin(), _observers.end(), &observer), _observers.end());
}

template <typename T>
void Subject<T>::notifyEvent(const T& event)
{
    for (Observer<T>* observer : _observers)
    {
        observer->receiveEvent(event);
    }
}

}