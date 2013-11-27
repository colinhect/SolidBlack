#include "Hect.h"

using namespace hect;

Flow::Flow() :
    _stateIndex(0)
{
}

void Flow::push(State* state)
{
    _states.push_back(std::shared_ptr<State>(state));
}

bool Flow::update(TimeSpan timeStep)
{
    _updateToTopState();
    
    State* state = _states[_stateIndex].get();
    while (!state->isActive())
    {
        _states.pop_back();
        --_stateIndex;

        if (_states.empty())
        {
            return false;
        }
        else
        {
            state = _states[_stateIndex].get();
            if (state->isSuspended())
            {
                state->resume();
                state->_suspended = false;

                _updateToTopState();
                state = _states[_stateIndex].get();
            }
        }
    }

    TimeSpan deltaTime = _timer.elapsed();
    _timer.reset();

    _accumulator += deltaTime;
    _delta += deltaTime;

    while (_accumulator.microseconds() >= timeStep.microseconds())
    {
        state->update(timeStep.seconds());

        _delta = TimeSpan();
        _accumulator -= timeStep;
    }

    state->render(_delta.seconds() / timeStep.seconds());

    return true;
}

void Flow::_updateToTopState()
{
    if (_stateIndex < _states.size() - 1)
    {
        if (_stateIndex < 0)
        {
            _stateIndex = 0;
        }

        for (; _stateIndex < _states.size() - 1; ++_stateIndex)
        {
            State* state = _states[_stateIndex].get();
            if (!state->isSuspended())
            {
                state->suspend();
                state->_suspended = true;
            }
        }

        ++_stateIndex;
    }
}