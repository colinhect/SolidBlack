#include "Hect.h"

using namespace hect;

const InputAxis& Input::axisWithName(const std::string& name) const
{
    auto it = _mappedAxes.find(name);
    if (it == _mappedAxes.end())
    {
        throw Error(format("No input axis '%s'", name.c_str()));
    }

    return *(*it).second;
}

void Input::setAxes(const InputAxis::Array& axes)
{
    _mappedAxes.clear();
    _axes = axes;

    for (InputAxis& axis : _axes)
    {
        _mappedAxes[axis.name()] = &axis;
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

void Input::notifyMouseEvent(const Mouse::Event& event)
{
    if (event.type == Mouse::Event::Movement)
    {
        double movementX = (double)event.cursorMovement.x;
        double movementY = (double)event.cursorMovement.y;

        for (InputAxis& axis : _axes)
        {

            if (axis.source() == InputAxis::MouseMoveX)
            {
                axis.setValue(axis.value() + movementX * axis.acceleration());
            }
            else if (axis.source() == InputAxis::MouseMoveY)
            {
                axis.setValue(axis.value() + movementY * axis.acceleration());
            }
        }
    }
    else if (event.type == Mouse::Event::ScrollUp || event.type == Mouse::Event::ScrollDown)
    {
        double movement = event.type == Mouse::Event::ScrollUp ? 1.0 : -1.0;

        for (InputAxis& axis : _axes)
        {
            if (axis.source() == InputAxis::MouseScroll)
            {
                axis.setValue(axis.value() + movement * axis.acceleration());
            }
        }
    }
}

Input::Input()
{
    _mouse.addListener(this);
}

void Input::_enqueueEvent(const Mouse::Event& event)
{
    _mouse._enqueueEvent(event);
}

void Input::_enqueueEvent(const Keyboard::Event& event)
{
    _keyboard._enqueueEvent(event);
}

void Input::_dispatchEvents()
{
    _mouse._dispatchEvents();
    _keyboard._dispatchEvents();
}

void Input::_update(double timeStep)
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

        if (axis.source() == InputAxis::Key)
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
        else if (axis.source() == InputAxis::MouseButton)
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