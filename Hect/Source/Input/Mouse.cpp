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

const Vector2<int>& Mouse::cursorPosition() const
{
    return _cursorPosition;
}

Dispatcher<MouseEvent>& Mouse::dispatcher()
{
    return _dispatcher;
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
        _dispatcher.notifyEvent(event);
    }

    _events.clear();
}