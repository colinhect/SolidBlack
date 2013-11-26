#include "Hect.h"

using namespace hect;

InputSystem::InputSystem()
{
    _mouse.addListener(*this);
}

InputSystem::InputSystem(const InputAxis::Array& axes) :
    _axes(axes)
{
    for (InputAxis& axis : _axes)
    {
        // Make sure an axis with the name does not already exist
        if (_mappedAxes.find(axis.name()) != _mappedAxes.end())
        {
            throw Error(format("Multiple input axes with name '%s'", axis.name().c_str()));
        }

        _mappedAxes[axis.name()] = &axis;
    }

    _mouse.addListener(*this);
}

const InputAxis& InputSystem::axisWithName(const std::string& name) const
{
    auto it = _mappedAxes.find(name);
    if (it == _mappedAxes.end())
    {
        throw Error(format("No input axis with name '%s'", name.c_str()));
    }

    return *(*it).second;
}

void InputSystem::updateAxes(double timeStep)
{
    for (InputAxis& axis : _axes)
    {
        double value = axis.value();
        double acceleration = axis.acceleration();
        double gravity = axis.gravity();

        // Gravitate towards zero
        if (gravity != 0)
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

Mouse& InputSystem::mouse()
{
    return _mouse;
}

Keyboard& InputSystem::keyboard()
{
    return _keyboard;
}

void InputSystem::receiveMouseEvent(const MouseEvent& event)
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
        double movement = event.type == MouseEventType::ScrollUp ? 1 : -1;

        for (InputAxis& axis : _axes)
        {
            if (axis.source() == InputAxisSource::MouseScroll)
            {
                axis.setValue(axis.value() + movement * axis.acceleration());
            }
        }
    }
}

void InputSystem::_enqueueEvent(const MouseEvent& event)
{
    _mouse._enqueueEvent(event);
}

void InputSystem::_enqueueEvent(const KeyboardEvent& event)
{
    _keyboard._enqueueEvent(event);
}

void InputSystem::_dispatchEvents()
{
    _mouse._dispatchEvents();
    _keyboard._dispatchEvents();
}