#include "Hect.h"

using namespace hect;

MouseEvent::MouseEvent() :
    type(MouseEventType::Movement),
    button(MouseButton::Left)
{
}

bool Mouse::isButtonDown(MouseButton button) const
{
    return _buttonStates[(int)button];
}

void Mouse::addListener(MouseListener& listener)
{
    if (std::find(_listeners.begin(), _listeners.end(), &listener) != _listeners.end())
    {
        return;  // This listener was already added
    }

    _listeners.push_back(&listener);
}

void Mouse::removeListener(MouseListener& listener)
{
    _listeners.erase(std::remove(_listeners.begin(), _listeners.end(), &listener), _listeners.end());
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

void Mouse::_enqueueEvent(const MouseEvent& event)
{
    _cursorPosition = event.cursorPosition;
    _events.push_back(event);
}

void Mouse::_dispatchEvents()
{
    for (const MouseEvent& event : _events)
    {
        for (MouseListener* listener : _listeners)
        {
            listener->receiveMouseEvent(event);
        }
    }

    _events.clear();
}