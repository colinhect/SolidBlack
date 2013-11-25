#include "Hect.h"

using namespace hect;

State::State(double timeStep) :
    _timeStep(timeStep),
    _active(true)
{
}

void State::begin(Flow& flow)
{
    flow;
}

void State::end(Flow& flow)
{
    flow;
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

double State::timeStep() const
{
    return _timeStep;
}

void State::setActive(bool active)
{
    _active = active;
}
