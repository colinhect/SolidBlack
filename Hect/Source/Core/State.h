#pragma once

namespace hect
{

///
/// A game state (e.g. main menu, single player game, credits).
class State
{
    friend class StateFlow;
public:

    ///
    /// A shared reference to a state.
    typedef std::shared_ptr<State> Ref;

    ///
    /// Constructs a state.
    State();

    virtual ~State() { }

    ///
    /// Returns whether the state is active.
    bool isActivated() const;

    ///
    /// Returns whether the state is done.
    bool isDone() const;

    ///
    /// Sets whether the state is done.
    ///
    /// \param done True if the state is done; false otherwise.
    void setDone(bool done);

protected:

    ///
    /// Called once every time step even if the state is not activated.
    ///
    /// \param timeStep The duration of time between each update (in seconds).
    virtual void update(double timeStep);

    ///
    /// Called when the a frame is rendered even if the state is not activated.
    ///
    /// \param delta The delta between the last call to update() and the next
    /// call to update() (useful for interpolation).
    virtual void render(double delta);

    ///
    /// Called when the state is made active.
    virtual void activate();

    ///
    /// Called when another state is made active.
    virtual void deactivate();

private:
    bool _activated;
    bool _done;
};

}