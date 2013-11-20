#pragma once

namespace hect
{

///
/// Provides access to input peripherals connected to the system.
class Input :
    public MouseListener
{
    friend class Engine;
public:

    ///
    /// Returns the axis with the given name.
    ///
    /// \param name The name of the axis.
    ///
    /// \throws Error If no axis with the name exists.
    const InputAxis& axisWithName(const std::string& name) const;

    ///
    /// Sets the input axes.
    ///
    /// \warning Invalidates any references to an existing axis.
    ///
    /// \param axes The new input axes.
    void setAxes(const InputAxis::Array& axes);

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
    Input();

    void _enqueueEvent(const MouseEvent& event);
    void _enqueueEvent(const KeyboardEvent& event);
    void _dispatchEvents();

    void _update(double timeStep);

    Mouse _mouse;
    Keyboard _keyboard;

    InputAxis::Array _axes;
    std::map<std::string, InputAxis*> _mappedAxes;
};

}