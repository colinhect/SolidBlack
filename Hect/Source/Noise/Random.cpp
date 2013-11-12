#include "Hect.h"

using namespace hect;

Random::Random(unsigned seed) :
    _current(seed)
{
}

unsigned Random::next()
{
    unsigned output = 0;

    for (int i = 0; i < 16; ++i)
    {
        _current = 3039177861 * _current + 1;
        unsigned temp = _current >> 30;

        output = output << 2;
        output = output + temp;
    }

    return output;
}

int Random::nextInt(int min, int max)
{
    assert(min < max);

    int range = max - min;
    unsigned n = next() % range;

    return min + n;
}

float Random::nextFloat(float min, float max)
{
    assert(min < max);

    float range = max - min;
    float n = ((float)(next() % 100000000) * 0.00000001f) * range;

    return min + n;
}

double Random::nextDouble(double min, double max)
{
    assert(min < max);

    double range = max - min;
    double n = ((double)(next() % 100000000) * 0.00000001) * range;

    return min + n;
}