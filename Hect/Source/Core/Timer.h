#pragma once

namespace hect
{

///
/// A utility for measuring time durations.
class Timer
{
public:

    ///
    /// Returns the total elapsed time since initialization.
    static TimeSpan totalElapsed();

    ///
    /// Constructs a timer and resets it.
    Timer();

    ///
    /// Resets the timer.
    void reset();

    ///
    /// Returns the elapsed time since the last reset.
    TimeSpan elapsed() const;

private:
    TimeSpan _start;
};

}