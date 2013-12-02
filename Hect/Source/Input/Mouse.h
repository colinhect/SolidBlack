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
/// Receives notifications of mouse events.
class MouseListener
{
public:
    virtual ~MouseListener() { }

    ///
    /// Notifies the listener of a mouse event.
    ///
    /// \param event The mouse event.
    virtual void receiveMouseEvent(const MouseEvent& event) = 0;
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
    /// Adds a listener to receive dispatched events.
    ///
    /// \remarks If the listener is already added then nothing happens.
    ///
    /// \param listener The listener to add.
    void addListener(MouseListener& listener);

    ///
    /// Removes a listener from receiving dispatched events.
    ///
    /// \remarks If the listener was not added then nothing happens.
    ///
    /// \param listener The listener to remove.
    void removeListener(MouseListener& listener);

    ///
    /// Returns the position of the cursor in window space.
    const Vector2<int>& cursorPosition() const;

private:
    Mouse();

    void _enqueueEvent(const MouseEvent& event);
    void _dispatchEvents();

    std::vector<MouseListener*> _listeners;
    std::vector<MouseEvent> _events;

    bool _cursorLocked;
    Vector2<int> _cursorPosition;

    std::vector<bool> _buttonStates;
};

};