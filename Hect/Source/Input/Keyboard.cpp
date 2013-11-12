#include "Hect.h"

using namespace hect;

Keyboard::Event::Event() :
    type(KeyDown),
    key(Key::Esc)
{
}

bool Keyboard::isKeyDown(Key key) const
{
    return _keyStates[key];
}

void Keyboard::addListener(Listener* listener)
{
    assert(listener);

    if (std::find(_listeners.begin(), _listeners.end(), listener) != _listeners.end())
    {
        return;  // This listener was already added
    }

    _listeners.push_back(listener);
}

void Keyboard::removeListener(Listener* listener)
{
    assert(listener);
    _listeners.erase(std::remove(_listeners.begin(), _listeners.end(), listener), _listeners.end());
}

Keyboard::Keyboard() :
    _keyStates(256, false)
{
}

void Keyboard::_enqueueEvent(const Event& event)
{
    _keyStates[event.key] = event.type == Event::Type::KeyDown;
    _events.push_back(event);
}

void Keyboard::_dispatchEvents()
{
    for (const Event& event : _events)
    {
        for (Listener* listener : _listeners)
        {
            listener->notifyKeyboardEvent(event);
        }
    }

    _events.clear();
}