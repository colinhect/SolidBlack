#pragma once

#include <Hect.h>
using namespace hect;

class DensitySampler
{
public:
    typedef std::shared_ptr<DensitySampler> Ref;

    DensitySampler(const AxisAlignedBox<>& area, Image::Ref top, Image::Ref side);

    double density(const Vector3<>& point, unsigned channel) const;

private:
    double _sampleTop(const Vector3<>& point, unsigned channel) const;
    double _sampleSide(const Vector3<>& point, unsigned channel) const;

    AxisAlignedBox<> _area;
    Image::Ref _top;
    Image::Ref _side;
};