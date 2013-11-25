#include "Hect.h"

using namespace hect;

Input::Input(const InputAxis::Array& axes) :
    _axes(axes)
{
    for (InputAxis& axis : _axes)
    {
        _mappedAxes[axis.name()] = &axis;
    }

    _mouse.addListener(*this);
}

const InputAxis& Input::axisWithName(const std::string& name) const
{
    auto it = _mappedAxes.find(name);
    if (it == _mappedAxes.end())
    {
        throw Error(format("No input axis '%s'", name.c_str()));
    }

    return *(*it).second;
}

void Input::updateAxes(double timeStep)
{
    for (InputAxis& axis : _axes)
    {
        double value = axis.value();
        double acceleration = axis.acceleration();
        double gravity = axis.gravity();

        // Gravitate towards zero
        if (gravity != 0.0f)
        {
            axis.setValue(value - value * std::min(1.0, gravity * timeStep));
        }

        if (axis.source() == InputAxisSource::Key)
        {
            if (_keyboard.isKeyDown(axis.positiveKey()))
            {
                axis.setValue(value + acceleration * timeStep);
            }

            if (_keyboard.isKeyDown(axis.negativeKey()))
            {
                axis.setValue(value - acceleration * timeStep);
            }
        }
        else if (axis.source() == InputAxisSource::MouseButton)
        {
            if (_mouse.isButtonDown(axis.positiveMouseButton()))
            {
                axis.setValue(value + acceleration * timeStep);
            }

            if (_mouse.isButtonDown(axis.negativeMouseButton()))
            {
                axis.setValue(value - acceleration * timeStep);
            }
        }
    }
}

Mouse& Input::mouse()
{
    return _mouse;
}

Keyboard& Input::keyboard()
{
    return _keyboard;
}

void Input::receiveMouseEvent(const MouseEvent& event)
{
    if (event.type == MouseEventType::Movement)
    {
        double movementX = (double)event.cursorMovement.x;
        double movementY = (double)event.cursorMovement.y;

        for (InputAxis& axis : _axes)
        {

            if (axis.source() == InputAxisSource::MouseMoveX)
            {
                axis.setValue(axis.value() + movementX * axis.acceleration());
            }
            else if (axis.source() == InputAxisSource::MouseMoveY)
            {
                axis.setValue(axis.value() + movementY * axis.acceleration());
            }
        }
    }
    else if (event.type == MouseEventType::ScrollUp || event.type == MouseEventType::ScrollDown)
    {
        double movement = event.type == MouseEventType::ScrollUp ? 1.0 : -1.0;

        for (InputAxis& axis : _axes)
        {
            if (axis.source() == InputAxisSource::MouseScroll)
            {
                axis.setValue(axis.value() + movement * axis.acceleration());
            }
        }
    }
}

void Input::_enqueueEvent(const MouseEvent& event)
{
    _mouse._enqueueEvent(event);
}

void Input::_enqueueEvent(const KeyboardEvent& event)
{
    _keyboard._enqueueEvent(event);
}

void Input::_dispatchEvents()
{
    _mouse._dispatchEvents();
    _keyboard._dispatchEvents();
}