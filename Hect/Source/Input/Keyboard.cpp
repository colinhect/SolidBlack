#include "Hect.h"

using namespace hect;

KeyboardEvent::KeyboardEvent() :
    type(KeyboardEventType::KeyDown),
    key(Key::Esc)
{
}

bool Keyboard::isKeyDown(Key key) const
{
    return _keyStates[(int)key];
}

void Keyboard::addListener(KeyboardListener& listener)
{
    if (std::find(_listeners.begin(), _listeners.end(), &listener) != _listeners.end())
    {
        return;  // This listener was already added
    }

    _listeners.push_back(&listener);
}

void Keyboard::removeListener(KeyboardListener& listener)
{
    _listeners.erase(std::remove(_listeners.begin(), _listeners.end(), &listener), _listeners.end());
}

Keyboard::Keyboard() :
    _keyStates(256, false)
{
}

void Keyboard::_enqueueEvent(const KeyboardEvent& event)
{
    _keyStates[(int)event.key] = event.type == KeyboardEventType::KeyDown;
    _events.push_back(event);
}

void Keyboard::_dispatchEvents()
{
    for (const KeyboardEvent& event : _events)
    {
        for (KeyboardListener* listener : _listeners)
        {
            listener->receiveKeyboardEvent(event);
        }
    }

    _events.clear();
}