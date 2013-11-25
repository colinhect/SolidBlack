#include "Hect.h"

using namespace hect;

void Flow::push(State* state)
{
    _states.push(std::shared_ptr<State>(state));
}

bool Flow::tick()
{
    // A new state was push on the stack
    if (_currentState && !_states.empty() && _currentState != _states.top())
    {
        _currentState->end(*this);
        _currentState = _states.top();
        _states.pop();

        _currentState->begin(*this);
        _timeStep = TimeSpan::fromSeconds(_currentState->timeStep());
            
        _timer.reset();
        _accumulator = TimeSpan();
        _delta = TimeSpan();
    }

    // We have no current state or the current state is inactive
    else if (!_currentState || !_currentState->isActive())
    {
        if (_states.empty())
        {
            return false;
        }

        _currentState = _states.top();
        _states.pop();

        _currentState->begin(*this);
        _timeStep = TimeSpan::fromSeconds(_currentState->timeStep());
            
        _timer.reset();
        _accumulator = TimeSpan();
        _delta = TimeSpan();
    }

    TimeSpan deltaTime = _timer.elapsed();
    _timer.reset();

    _accumulator += deltaTime;
    _delta += deltaTime;

    while (_accumulator.microseconds() >= _timeStep.microseconds())
    {
        _currentState->update(_timeStep.seconds());

        _delta = TimeSpan();
        _accumulator -= _timeStep;
    }

    _currentState->render(_delta.seconds() / _timeStep.seconds());

    return true;
}