#include "Hect.h"

using namespace hect;

State::State() :
    _active(true),
    _suspended(false)
{
}

void State::suspend()
{
}

void State::resume()
{
}

void State::update(double timeStep)
{
    timeStep;
}

void State::render(double delta)
{
    delta;
}

bool State::isActive() const
{
    return _active;
}

bool State::isSuspended() const
{
    return _suspended;
}

void State::setActive(bool active)
{
    _active = active;
}
