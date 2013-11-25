#pragma once

namespace hect
{

///
/// Updates behaviors in stages.
class BehaviorSystem :
    public System
{
public:

    ///
    /// Constructs the system.
    BehaviorSystem();

    ///
    /// Updates all of the behaviors in stages.
    ///
    /// \param timeStep The time between last frame and this one.
    void update(double timeStep);
};

}