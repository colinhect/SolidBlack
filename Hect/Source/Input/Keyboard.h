namespace hect
{

///
/// Provides access to the system keyboard.
class Keyboard
{
    friend class Input;
public:

    ///
    /// A key on a keyboard.
    enum Key
    {
        A = 0,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Num0 = 26,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Esc = 36,
        Ctrl,
        Shift,
        Alt,
        Space = 57,
        Enter,
        Backspace,
        Tab,
        Tick = 54,
        F1 = 85,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12
    };

    ///
    /// An event triggered by pressing or releasing a key on the keyboard.
    class Event
    {
    public:

        ///
        /// A keyboard event type.
        enum Type
        {
            ///
            /// A key was pressed down.
            KeyDown,

            ///
            /// A key was released up.
            KeyUp
        };

        ///
        /// Constructs a default event.
        Event();

        ///
        /// The type of the event.
        Type type;

        ///
        /// The key relating to the event.
        Key key;
    };

    ///
    /// Receives notifications of keyboard events.
    class Listener
    {
    public:
        virtual ~Listener() { }

        ///
        /// Notifies the listener of a keyboard event.
        ///
        /// \param event The keyboard event.
        virtual void notifyKeyboardEvent(const Event& event) = 0;
    };

    ///
    /// Returns whether the given key is down.
    ///
    /// \param key The key to check if it is down.
    bool isKeyDown(Key key) const;

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

private:
    Keyboard();

    void _enqueueEvent(const Event& event);
    void _dispatchEvents();

    std::vector<Listener*> _listeners;
    std::vector<Event> _events;

    std::vector<bool> _keyStates;
};

};