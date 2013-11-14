#include "Hect.h"

using namespace hect;

State::State(Engine& engine, double timeStep) :
    _engine(&engine),
    _timeStep(timeStep),
    _active(true)
{
}

void State::begin()
{
}

void State::end()
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

double State::timeStep() const
{
    return _timeStep;
}

Engine& State::engine()
{
    return *_engine;
}

void State::setActive(bool active)
{
    _active = active;
}
