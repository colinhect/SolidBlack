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

Dispatcher<KeyboardEvent>& Keyboard::dispatcher()
{
    return _dispatcher;
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
        _dispatcher.notifyEvent(event);
    }
    _events.clear();
}