#pragma once

namespace hect
{

///
/// An abstract behavior.
///
/// \remarks Multiple update stages are exposed to allow well-defined ordering
/// of events amongst behaviors.
class Behavior :
    public Component<Behavior>
{
public:

    ///
    /// First update stage.
    ///
    /// \param timeStep The time between last frame and this one.
    virtual void preUpdate(double timeStep);

    ///
    /// Second update stage.
    ///
    /// \param timeStep The time between last frame and this one.
    virtual void update(double timeStep);

    ///
    /// Third update stage.
    ///
    /// \param timeStep The time between last frame and this one.
    virtual void postUpdate(double timeStep);
};

}