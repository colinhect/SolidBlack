namespace hect
{

template <typename T>
void Dispatcher<T>::addListener(Listener<T>& listener)
{
    auto it = std::find(_listeners.begin(), _listeners.end(), &listener);
    if (it == _listeners.end())
    {
        _listeners.push_back(&listener);
    }
}

template <typename T>
void Dispatcher<T>::removeListener(Listener<T>& listener)
{
    auto it = std::find(_listeners.begin(), _listeners.end(), &listener);
    if (it != _listeners.end())
    {
        _listeners.erase(it);
    }
}

template <typename T>
void Dispatcher<T>::notifyEvent(const T& event)
{
    for (Listener<T>* listener : _listeners)
    {
        listener->receiveEvent(event);
    }
}

}