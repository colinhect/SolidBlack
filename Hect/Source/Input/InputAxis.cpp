#include "Hect.h"

using namespace hect;

InputAxis::InputAxis(const std::string& name, Source source) :
    _name(name),
    _source(source),
    _positiveMouseButton(Mouse::Left),
    _negativeMouseButton(Mouse::Right),
    _positiveKey(Keyboard::A),
    _negativeKey(Keyboard::B),
    _value(0),
    _acceleration(1),
    _gravity(0)
{
}

const std::string& InputAxis::name() const
{
    return _name;
}

InputAxis::Source InputAxis::source() const
{
    return _source;
}

Mouse::Button InputAxis::positiveMouseButton() const
{
    return _positiveMouseButton;
}

void InputAxis::setPositiveMouseButton(Mouse::Button button)
{
    _positiveMouseButton = button;
}

Mouse::Button InputAxis::negativeMouseButton() const
{
    return _negativeMouseButton;
}

void InputAxis::setNegativeMouseButton(Mouse::Button button)
{
    _negativeMouseButton = button;
}

Keyboard::Key InputAxis::positiveKey() const
{
    return _positiveKey;
}

void InputAxis::setPositiveKey(Keyboard::Key key)
{
    _positiveKey = key;
}

Keyboard::Key InputAxis::negativeKey() const
{
    return _negativeKey;
}

void InputAxis::setNegativeKey(Keyboard::Key key)
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