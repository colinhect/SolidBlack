#include "Hect.h"

using namespace hect;

Mouse::Event::Event() :
    type(Movement),
    button(Button::Left)
{
}

bool Mouse::isButtonDown(Button button) const
{
    return _buttonStates[button];
}

void Mouse::addListener(Listener* listener)
{
    assert(listener);

    if (std::find(_listeners.begin(), _listeners.end(), listener) != _listeners.end())
    {
        return;  // This listener was already added
    }

    _listeners.push_back(listener);
}

void Mouse::removeListener(Listener* listener)
{
    assert(listener);
    _listeners.erase(std::remove(_listeners.begin(), _listeners.end(), listener), _listeners.end());
}

void Mouse::setCursorLocked(bool locked)
{
    _cursorLocked = locked;
}

bool Mouse::isCursorLocked() const
{
    return _cursorLocked;
}

const Vector2<int>& Mouse::cursorPosition() const
{
    return _cursorPosition;
}

Mouse::Mouse() :
    _cursorLocked(false),
    _buttonStates(16, false)
{
}

void Mouse::_enqueueEvent(const Event& event)
{
    _cursorPosition = event.cursorPosition;
    _events.push_back(event);
}

void Mouse::_dispatchEvents()
{
    for (const Event& event : _events)
    {
        for (Listener* listener : _listeners)
        {
            listener->notifyMouseEvent(event);
        }
    }

    _events.clear();
}