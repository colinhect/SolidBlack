#pragma once

namespace hect
{

class LogicLayer
{
public:
    virtual ~LogicLayer() { }

    ///
    /// Called once every time step.
    ///
    /// \param timeStep The duration of time between each update (in seconds).
    virtual void update(double timeStep) { timeStep; }

    ///
    /// Called when the a frame is rendered.
    ///
    /// \param delta The delta between the last call to update() and the next
    /// call to update() (useful for interpolation).
    virtual void render(double delta) { delta; }
};

}