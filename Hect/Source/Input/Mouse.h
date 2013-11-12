namespace hect
{

///
/// Provides access to the system mouse.
class Mouse
{
    friend class Input;
public:

    ///
    /// A mouse button.
    enum Button
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
    /// An event caused by the alteration of the mouse.
    class Event
    {
    public:

        ///
        /// A mouse event type.
        enum Type
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
        /// Constructs a default event.
        Event();

        ///
        /// The type of the event.
        Type type;

        ///
        /// The mouse button related to the event.
        ///
        /// \remarks Only relevant for a Mouse::Event::ButtonDown or
        /// Mouse::Event::ButtonUp event.
        Button button;

        ///
        /// The coordinates of the cursor.
        Vector2<int> cursorPosition;

        ///
        /// The movement of the cursor.
        Vector2<int> cursorMovement;
    };

    ///
    /// Receives notifications of mouse events.
    class Listener
    {
    public:
        virtual ~Listener() { }

        ///
        /// Notifies the listener of a mouse event.
        ///
        /// \param event The mouse event.
        virtual void notifyMouseEvent(const Event& event) = 0;
    };

    ///
    /// Returns whether the given button is down.
    ///
    /// \param button The button to check if it is down.
    bool isButtonDown(Button button) const;

    ///
    /// Adds a listener to receive dispatched events.
    ///
    /// \remarks If the listener is already added then nothing happens.
    ///
    /// \param listener The listener to add.
    void addListener(Listener* listener);

    ///
    /// Removes a listener from receiving dispatched events.
    ///
    /// \remarks If the listener was not added then nothing happens.
    ///
    /// \param listener The listener to remove.
    void removeListener(Listener* listener);

    ///
    /// Sets whether the cursor is locked at the center of the screen.
    ///
    /// \param locked Whether the cursor is locked.
    void setCursorLocked(bool locked);

    ///
    /// Returns whether the cursor is locked.
    bool isCursorLocked() const;

    ///
    /// Returns the position of the cursor in screen space.
    const Vector2<int>& cursorPosition() const;

private:
    Mouse();

    void _enqueueEvent(const Event& event);
    void _dispatchEvents();

    std::vector<Listener*> _listeners;
    std::vector<Event> _events;

    bool _cursorLocked;
    Vector2<int> _cursorPosition;

    std::vector<bool> _buttonStates;
};

};