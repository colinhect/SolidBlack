#pragma once

namespace hect
{

///
/// A mouse button.
enum class MouseButton
{
    ///
    /// The left mouse button.
    Left,

    ///
    /// The right mouse button.
    Right,

    ///
    /// The middle mouse button.
    Middle
};

///
/// A mouse event type.
enum class MouseEventType
{
    ///
    /// The mouse was moved.
    Movement,

    ///
    /// A mouse button was pressed down.
    ButtonDown,

    ///
    /// A mouse button was released up.
    ButtonUp,

    ///
    /// The scroll wheel was moved down.
    ScrollDown,

    ///
    /// The scroll wheel was moved up.
    ScrollUp
};

///
/// An event caused by the alteration of the mouse.
class MouseEvent
{
public:

    ///
    /// Constructs a default event.
    MouseEvent();

    ///
    /// The type of the event.
    MouseEventType type;

    ///
    /// The mouse button related to the event.
    ///
    /// \remarks Only relevant for a MouseEvent::ButtonDown or
    /// MouseEvent::ButtonUp event.
    MouseButton button;

    ///
    /// The coordinates of the cursor.
    Vector2<int> cursorPosition;

    ///
    /// The movement of the cursor.
    Vector2<int> cursorMovement;
};

///
/// Provides access to the system mouse.
class Mouse
{
    friend class InputSystem;
public:

    ///
    /// Returns whether the given button is down.
    ///
    /// \param button The button to check if it is down.
    bool isButtonDown(MouseButton button) const;

    ///
    /// Returns the position of the cursor in window space.
    const Vector2<int>& cursorPosition() const;

    ///
    /// Returns the dispatcher of mouse events.
    Dispatcher<MouseEvent>& dispatcher();

private:
    Mouse();

    void _enqueueEvent(const MouseEvent& event);
    void _dispatchEvents();

    Dispatcher<MouseEvent> _dispatcher;
    std::vector<MouseEvent> _events;

    bool _cursorLocked;
    Vector2<int> _cursorPosition;

    std::vector<bool> _buttonStates;
};

};