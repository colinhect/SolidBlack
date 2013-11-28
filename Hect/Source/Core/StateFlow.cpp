#include "Hect.h"

using namespace hect;

StateFlow::StateFlow() :
    _stateIndex(-1)
{
}

void StateFlow::push(State::Ref state)
{
    _states.push_back(state);
}

bool StateFlow::transition()
{
    _ensureHighestState();
    
    State::Ref state = _states.back();
    while (state->isDone())
    {
        // Pop the topmost state
        _states.pop_back();
        --_stateIndex;

        // Deactivate the state was done
        if (state->isActivated())
        {
            state->deactivate();
            state.reset();

            // The deactivation/destructor may have pushed a state
            _ensureHighestState();
        }

        // Check if we are out of states
        if (_states.empty())
        {
            return false;
        }

        state = _states.back();
    }

    return true;
}

void StateFlow::update(TimeSpan timeStep)
{
    TimeSpan deltaTime = _timer.elapsed();
    _timer.reset();

    _accumulator += deltaTime;
    _delta += deltaTime;

    while (_accumulator.microseconds() >= timeStep.microseconds())
    {
        // Update the states
        for (const State::Ref& state : _states)
        {
            state->update(timeStep.seconds());
        }

        _delta = TimeSpan();
        _accumulator -= timeStep;
    }

    // Render the states
    for (const State::Ref& state : _states)
    {
        state->render(_delta.seconds() / timeStep.seconds());
    }
}

void StateFlow::_ensureHighestState()
{
    // If we are not at the highest state
    if (_stateIndex < (int)_states.size() - 1)
    {
        // Special case if this is the first state we are activating
        if (_stateIndex < 0)
        {
            _stateIndex = 0;
        }

        // Move to the top of the stack and deactivated any activated
        // states along the way
        for (; _stateIndex < (int)_states.size() - 1; ++_stateIndex)
        {
            State::Ref state = _states[_stateIndex];
            if (state->isActivated())
            {
                state->deactivate();
                state->_activated = false;
            }
        }
    }

    if (!_states.empty())
    {
        // Activate the top state if needed
        State::Ref state = _states.back();
        if (!state->isActivated())
        {
            state->activate();
            state->_activated = true;

            // The activation may have pushed a state
            _ensureHighestState();
        }
    }
}