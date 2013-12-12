#pragma once

namespace hect
{

///
/// A layer of logic within a flow.
class LogicLayer
{
public:
    LogicLayer();
    virtual ~LogicLayer() { }

    ///
    /// Called once every time step.
    ///
    /// \param timeStep The duration of time between each fixed update (in
    /// seconds).
    virtual void fixedUpdate(double timeStep);

    ///
    /// Called once every frame.
    ///
    /// \param delta The delta between the last fixed update and the next
    /// fixed update.
    virtual void frameUpdate(double delta);

    ///
    /// Returns whether the layer is active.
    bool isActive() const;

    ///
    /// Sets whether the layer is active.
    ///
    /// \param active True if the layer is active; false otherwise.
    void setActive(bool active);

private:
    bool _active;
};

}