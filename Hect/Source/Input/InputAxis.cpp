#include "Hect.h"

using namespace hect;

InputAxis::InputAxis(const std::string& name, InputAxisSource source) :
    _name(name),
    _source(source),
    _positiveMouseButton(MouseButton::Left),
    _negativeMouseButton(MouseButton::Right),
    _positiveKey(Key::A),
    _negativeKey(Key::B),
    _value(0),
    _acceleration(1),
    _gravity(0)
{
}

const std::string& InputAxis::name() const
{
    return _name;
}

InputAxisSource InputAxis::source() const
{
    return _source;
}

MouseButton InputAxis::positiveMouseButton() const
{
    return _positiveMouseButton;
}

void InputAxis::setPositiveMouseButton(MouseButton button)
{
    _positiveMouseButton = button;
}

MouseButton InputAxis::negativeMouseButton() const
{
    return _negativeMouseButton;
}

void InputAxis::setNegativeMouseButton(MouseButton button)
{
    _negativeMouseButton = button;
}

Key InputAxis::positiveKey() const
{
    return _positiveKey;
}

void InputAxis::setPositiveKey(Key key)
{
    _positiveKey = key;
}

Key InputAxis::negativeKey() const
{
    return _negativeKey;
}

void InputAxis::setNegativeKey(Key key)
{
    _negativeKey = key;
}

double InputAxis::value() const
{
    return _value;
}

void InputAxis::setValue(double value)
{
    _value = value;
    _value = std::max(-1.0, _value);
    _value = std::min(1.0, _value);
}

double InputAxis::acceleration() const
{
    return _acceleration;
}

void InputAxis::setAcceleration(double acceleration)
{
    _acceleration = acceleration;
}

double InputAxis::gravity() const
{
    return _gravity;
}

void InputAxis::setGravity(double gravity)
{
    _gravity = gravity;
}