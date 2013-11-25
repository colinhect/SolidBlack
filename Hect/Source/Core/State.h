#pragma once

namespace hect
{

class Flow;

///
/// A state in a flow (e.g. main menu, single player game, credits).
class State
{
public:

    ///
    /// Constructs a state given its the time step.
    ///
    /// \param timeStep The duration of time between each update (in seconds).
    State(double timeStep);
    virtual ~State() { }

    ///
    /// Called when the state begins.
    ///
    /// \param flow The flow.
    virtual void begin(Flow& flow);

    ///
    /// Called when the state ends.
    ///
    /// \param flow The flow.
    virtual void end(Flow& flow);

    ///
    /// Called once every time step.
    ///
    /// \param timeStep The duration of time between each update (in seconds).
    virtual void update(double timeStep);

    ///
    /// Called when the a frame is rendered.
    ///
    /// \param delta The delta between the last call to update() and the next
    /// call to update() (useful for interpolation).
    virtual void render(double delta);

    ///
    /// Returns whether the state is active.
    bool isActive() const;

    ///
    /// Returns the time between each frame.
    double timeStep() const;

protected:

    ///
    /// Sets whether the state is active.
    ///
    /// \remarks When the current state of the engine is no longer active
    /// it will end and the next state on the stack will begin.
    ///
    /// \param active True if the state is active; false otherwise.
    void setActive(bool active);

private:
    double _timeStep;
    bool _active;
};

}