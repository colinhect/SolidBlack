#include "Hect.h"

using namespace hect;

State::State() :
    _activated(false),
    _done(false)
{
}

bool State::isActivated() const
{
    return _activated;
}

bool State::isDone() const
{
    return _done;
}

void State::setDone(bool done)
{
    _done = done;
}

void State::update(double timeStep)
{
    timeStep;
}

void State::render(double delta)
{
    delta;
}

void State::activate()
{
}

void State::deactivate()
{
}