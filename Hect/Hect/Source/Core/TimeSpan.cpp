#include "Hect.h"

using namespace hect;

TimeSpan TimeSpan::fromMicroseconds(int64_t microseconds)
{
    return TimeSpan(microseconds);
}

TimeSpan TimeSpan::fromMilliseconds(int64_t milliseconds)
{
    return TimeSpan(milliseconds * 1000);
}

TimeSpan TimeSpan::fromSeconds(double seconds)
{
    return TimeSpan((int64_t)(seconds * 1000.0 * 1000.0));
}

TimeSpan::TimeSpan() :
    _microseconds(0)
{
}

int64_t TimeSpan::microseconds()
{
    return _microseconds;
}

int64_t TimeSpan::milliseconds()
{
    return _microseconds / 1000;
}

double TimeSpan::seconds()
{
    return (double)(milliseconds()) / 1000.0;
}

TimeSpan TimeSpan::operator+(const TimeSpan& t) const
{
    return TimeSpan(_microseconds + t._microseconds);
}

TimeSpan TimeSpan::operator-(const TimeSpan& t) const
{
    return TimeSpan(_microseconds - t._microseconds);
}

TimeSpan TimeSpan::operator*(double value) const
{
    return TimeSpan((int64_t)(value * _microseconds));
}

TimeSpan TimeSpan::operator/(double value) const
{
    return TimeSpan((int64_t)((double)(_microseconds) / value));
}

TimeSpan TimeSpan::operator-() const
{
    return TimeSpan(-_microseconds);
}

TimeSpan& TimeSpan::operator+=(const TimeSpan& t)
{
    _microseconds += t._microseconds;
    return *this;
}

TimeSpan& TimeSpan::operator-=(const TimeSpan& t)
{
    _microseconds -= t._microseconds;
    return *this;
}

TimeSpan& TimeSpan::operator*=(double value)
{
    _microseconds = (int64_t)(value * _microseconds);
    return *this;
}

TimeSpan& TimeSpan::operator/=(double value)
{
    _microseconds = (int64_t)((double)(_microseconds) / value);
    return *this;
}

TimeSpan::TimeSpan(int64_t microseconds) :
    _microseconds(microseconds)
{
}