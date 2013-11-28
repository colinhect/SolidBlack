#pragma once

namespace hect
{

///
/// Provides access to input peripherals connected to the system.
class InputSystem :
    public MouseListener
{
    friend class Window;
public:

    ///
    /// Constructs an input system without any axes.
    InputSystem();

    ///
    /// Constructs an input system given axes.
    ///
    /// \param axes The input axes to include in the system.
    ///
    /// \throws Error If there are multiple axes with the same name.
    InputSystem(const InputAxis::Array& axes);

    ///
    /// Returns the axis with the given name.
    ///
    /// \param name The name of the axis.
    ///
    /// \throws Error If no axis with the name exists.
    const InputAxis& axisWithName(const std::string& name) const;

    ///
    /// Updates all input axes in the system.
    ///
    /// \param timeStep The duration of time between each update (in seconds).
    void updateAxes(double timeStep);

    ///
    /// Returns the mouse connected to the system.
    Mouse& mouse();

    ///
    /// Returns the keyboard connected to the system.
    Keyboard& keyboard();

    ///
    /// \copydoc MouseListener::receiveMouseEvent()
    void receiveMouseEvent(const MouseEvent& event);

private:
    void _enqueueEvent(const MouseEvent& event);
    void _enqueueEvent(const KeyboardEvent& event);
    void _dispatchEvents();

    Mouse _mouse;
    Keyboard _keyboard;

    InputAxis::Array _axes;
    std::map<std::string, InputAxis*> _mappedAxes;
};

}