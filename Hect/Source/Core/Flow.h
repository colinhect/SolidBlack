#pragma once

namespace hect
{

///
/// Manages the flow of states
class Flow :
    public Uncopyable
{
public:

    /// Constructs a flow.
    Flow();

    ///
    /// Pushes a new state onto the stack.
    ///
    /// \param state The state (the flow will maintain ownership of the state).
    void push(State* state);
    
    ///
    /// Progresses the flow.
    ///
    /// \param timeStep The duration of time between each update (in seconds).
    ///
    /// \returns True if there are still states to execute, false if there are
    /// no other states in the flow.
    bool update(TimeSpan timeStep);

private:
    void _updateToTopState();

    Timer _timer;
    TimeSpan _accumulator;
    TimeSpan _delta;

    int _stateIndex;
    std::vector<std::shared_ptr<State>> _states;
};

}