#pragma once

namespace hect
{

///
/// A flow of states.
class Flow :
    public Uncopyable
{
public:

    ///
    /// Pushes a new state onto the stack.
    ///
    /// \param state The state (the flow will maintain ownership of the state).
    void push(State* state);
    
    ///
    /// Updates the current state and potentially moves to the next state as
    /// needed.
    //
    /// \returns True if there are still states to execute, false if there are
    /// no other states in the flow.
    bool tick();

private:
    Timer _timer;
    TimeSpan _timeStep;
    TimeSpan _accumulator;
    TimeSpan _delta;

    std::shared_ptr<State> _currentState;
    std::stack<std::shared_ptr<State>> _states;
};

}