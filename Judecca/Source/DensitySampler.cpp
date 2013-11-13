#include "DensitySampler.h"

DensitySampler::DensitySampler(const AxisAlignedBox<>& area, Image::Ref top, Image::Ref side) :
    _area(area),
    _top(top),
    _side(side)
{
}

double DensitySampler::density(const Vector3<>& point, unsigned channel) const
{
    return _sampleTop(point, channel) * _sampleSide(point, channel);
}

double DensitySampler::_sampleTop(const Vector3<>& point, unsigned channel) const
{
    unsigned bpp = _top->bytesPerPixel();
    unsigned width = _top->width();
    unsigned height = _top->height();

    Vector3<> relativePoint = point;
    relativePoint -= _area.minimum();
    relativePoint /= _area.maximum() - _area.minimum();

    unsigned x = (unsigned)(relativePoint.x * (width - 1));
    unsigned z = (unsigned)(relativePoint.z * (height - 1));

    x = std::min(width - 1, std::max(0u, x));
    z = std::min(height - 1, std::max(0u, z));

    return (double)_top->pixelData()[z * width * bpp + x * bpp + channel] / 255.0;
}

double DensitySampler::_sampleSide(const Vector3<>& point, unsigned channel) const
{
    unsigned bpp = _side->bytesPerPixel();
    unsigned width = _side->width();
    unsigned height = _side->height();

    double actualWidth = (_area.maximum().x - _area.minimum().x) / 2.0;
    double actualHeight = _area.maximum().y - _area.minimum().y;

    double u = Vector2<>(point.x, point.z).length();
    u /= actualWidth;
    u = std::min(1.0, std::max(0.0, u));

    double v = point.y;
    v /= actualHeight;
    v += 0.5;

    unsigned x = (unsigned)(u * (width - 1));
    unsigned y = (unsigned)(v * (height - 1));

    x = std::min(width - 1, std::max(0u, x));
    y = std::min(height - 1, std::max(0u, y));

    return (double)_side->pixelData()[y * width * bpp + x * bpp + channel] / 255.0;
}