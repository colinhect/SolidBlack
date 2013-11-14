namespace hect
{

///
/// Provides the functionality for generating psuedo-random numbers.
class Random
{
public:

    ///
    /// Constructs a random number generator given a seed.
    ///
    /// \param seed The initial seed.
    Random(unsigned seed);

    ///
    /// Returns the next random number.
    unsigned next();

    ///
    /// Returns the next random number as an integer within a range.
    ///
    /// \param min The minimum value (must be less than max).
    /// \param max The maximum value (must be more than min).
    int nextInt(int min, int max);

    ///
    /// Returns the next random number as a float within a range.
    ///
    /// \param min The minimum value (must be less than max).
    /// \param max The maximum value (must be more than min).
    float nextFloat(float min, float max);

    ///
    /// Returns the next random number as a double within a range.
    ///
    /// \param min The minimum value (must be less than max).
    /// \param max The maximum value (must be more than min).
    double nextDouble(double min, double max);

private:
    unsigned _current;
};

}