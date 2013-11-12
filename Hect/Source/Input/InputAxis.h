namespace hect
{

///
/// An axis manipulated by an input device.
class InputAxis
{
public:

    ///
    /// An array of input axes.
    typedef std::vector<InputAxis> Array;

    ///
    /// The source of an input axis.
    enum Source
    {
        ///
        /// A mouse movement along the x axis.
        MouseMoveX,

        ///
        /// A mouse movement along the y axis.
        MouseMoveY,

        ///
        /// A mouse button press.
        MouseButton,

        ///
        /// A mouse scroll.
        MouseScroll,

        ///
        /// A key press.
        Key
    };

    ///
    /// Constructs an input axis.
    ///
    /// \param name The name of the axis (must be unique).
    /// \param source The source of the axis.
    InputAxis(const std::string& name, Source source);

    ///
    /// Returns the name.
    const std::string& name() const;

    ///
    /// Returns the source.
    Source source() const;

    ///
    /// Returns the mouse button which causes the axis to move in the positive
    /// direction.
    Mouse::Button positiveMouseButton() const;

    ///
    /// Sets the mouse button which causes the axis to move in the positive
    /// direction.
    ///
    /// \param button The new button.
    void setPositiveMouseButton(Mouse::Button button);

    ///
    /// Returns the mouse button which causes the axis to move in the negative
    /// direction.
    Mouse::Button negativeMouseButton() const;

    ///
    /// Sets the mouse button which causes the axis to move in the negative
    /// direction.
    ///
    /// \param button The new button.
    void setNegativeMouseButton(Mouse::Button button);

    ///
    /// Returns the key which causes the axis to move in the positive
    /// direction.
    Keyboard::Key positiveKey() const;

    ///
    /// Sets the key which causes the axis to move in the positive direction.
    ///
    /// \param key The new key.
    void setPositiveKey(Keyboard::Key key);

    ///
    /// Returns the key which causes the axis to move in the negative
    /// direction.
    Keyboard::Key negativeKey() const;

    ///
    /// Sets the key which causes the axis to move in the negative direction.
    ///
    /// \param key The new key.
    void setNegativeKey(Keyboard::Key key);

    ///
    /// Returns the current value.
    double value() const;

    ///
    /// Sets the current value.
    ///
    /// \param value The new value.
    void setValue(double value);

    ///
    /// Returns the acceleration.
    double acceleration() const;

    ///
    /// Sets the acceleration.
    ///
    /// \param acceleration The new acceleration.
    void setAcceleration(double acceleration);

    ///
    /// Returns the gravity.
    double gravity() const;

    ///
    /// Sets the gravity.
    ///
    /// \param gravity The new gravity.
    void setGravity(double gravity);

private:
    std::string _name;
    Source _source;

    Mouse::Button _positiveMouseButton;
    Mouse::Button _negativeMouseButton;

    Keyboard::Key _positiveKey;
    Keyboard::Key _negativeKey;

    double _value;
    double _acceleration;
    double _gravity;
};

}