#include "Hect.h"

using namespace hect;

#include <SFML/System.hpp>

TimeSpan Timer::totalElapsed()
{
    static sf::Clock clock;
    return TimeSpan::fromMicroseconds(clock.getElapsedTime().asMicroseconds());
}

Timer::Timer()
{
    reset();
}

void Timer::reset()
{
    _start = totalElapsed();
}

TimeSpan Timer::elapsed() const
{
    return totalElapsed() - _start;
}