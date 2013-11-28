#pragma once

namespace hect
{

///
/// Manages the flow of states as a stack.
class StateFlow :
    public Uncopyable
{
public:

    ///
    /// Constructs a state flow.
    StateFlow();

    ///
    /// Pushes a new state onto the flow stack.
    ///
    /// \param state The state.
    void push(State::Ref state);

    ///
    /// If there are new states above the activated state then the activated
    /// state is deactivated and the state at the top of the stack is
    /// activated.  If the activated state is done then the activated state is
    /// deactivated and the state below it is activated.
    ///
    /// \returns True if there are still states to execute on the flow stack;
    /// false otherwise.
    bool transition();

    ///
    /// Updates all states on the flow stack.
    ///
    /// \param timeStep The duration of time between each update (in seconds).
    void update(TimeSpan timeStep);

private:
    void _ensureHighestState();

    Timer _timer;
    TimeSpan _accumulator;
    TimeSpan _delta;

    int _stateIndex;
    std::vector<State::Ref> _states;
};

}