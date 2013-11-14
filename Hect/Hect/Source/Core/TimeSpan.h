namespace hect
{

///
/// A duration of time.
class TimeSpan
{
public:

    ///
    /// Creates a time span from microseconds.
    ///
    /// \param microseconds The duration of time in microseconds.
    static TimeSpan fromMicroseconds(int64_t microseconds);

    ///
    /// Creates a time span from milliseconds.
    ///
    /// \param milliseconds The duration of time in milliseconds.
    static TimeSpan fromMilliseconds(int64_t milliseconds);

    ///
    /// Creates a time span from seconds.
    ///
    /// \param seconds The duration of time in seconds.
    static TimeSpan fromSeconds(double seconds);

    ///
    /// Constructs a timespan of zero seconds.
    TimeSpan();

    ///
    /// Returns the time span in microseconds.
    int64_t microseconds();

    ///
    /// Returns the time in milliseconds.
    int64_t milliseconds();

    ///
    /// Returns the time in seconds.
    double seconds();

    ///
    /// Returns the sum of the time span and another time span.
    ///
    /// \param t The time span to compute the sum with.
    TimeSpan operator+(const TimeSpan& t) const;

    ///
    /// Returns the difference of the time span and another time span.
    ///
    /// \param t The time span to compute the difference with.
    TimeSpan operator-(const TimeSpan& t) const;

    ///
    /// Returns the product of the time span and a scalar.
    ///
    /// \param value The scalar to compute the product with.
    TimeSpan operator*(double value) const;

    ///
    /// Returns the quotient of the time span and a scalar.
    ///
    /// \param value The scalar to compute the quotient with.
    TimeSpan operator/(double value) const;

    ///
    /// Returns a negated copy of the time span.
    TimeSpan operator-() const;

    ///
    /// Adds a time span to the time span.
    ///
    /// \param t The time span to add.
    ///
    /// \returns A reference to the time span.
    TimeSpan& operator+=(const TimeSpan& t);

    ///
    /// Subtracts a time span from the time span.
    ///
    /// \param t The time span to subtract.
    ///
    /// \returns A reference to the time span.
    TimeSpan& operator-=(const TimeSpan& t);

    ///
    /// Multiplies the time span by a scalar.
    ///
    /// \param value The value to multiply by.
    ///
    /// \returns A reference to the time span.
    TimeSpan& operator*=(double value);

    ///
    /// Divides the time span by a scalar.
    ///
    /// \param value The value to divide by.
    ///
    /// \returns A reference to the time span.
    TimeSpan& operator/=(double value);

private:
    TimeSpan(int64_t microseconds);

    int64_t _microseconds;
};

}